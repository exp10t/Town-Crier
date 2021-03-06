# Town Crier: An Authenticated Data Feed For Smart Contracts

Smart contracts systems today lack trustworthy sources of data, as currently
deployed oracles provide only weak provenance and confidentiality guarantees.
The Town Crier (TC) system leverages trusted hardware (Intel SGX) to provide a
strong guarantee that data comes from an existing, trustworthy source. It also
provides confidentiality, enabling smart contracts to support confidential
queries and manage user credentials.

Please read on for installation instructions. If you want to learn how Town Crier works,
you can read our [CCS'16 paper](https://www.cs.cornell.edu/~fanz/files/pubs/tc-ccs16-final.pdf).

# Get Started

## Using Docker (recommended)

First, make sure Docker is ready. This usually can be verified by running

    docker run hello-world

If you see reasonable output from the above command, then your Docker setup
should be good to go.

Second, pull the docker iamge and clone the source code 

    docker pull bl4ck5un/intel-sgx-sdk-ubuntu-16.04
    git clone https://github.com/bl4ck5un/Town-Crier
    cd Town-Crier

Then, use `docker run` to get an shell, then you can use it to build and run
Town Crier:

    docker run -v $(PWD):/home/tc/TownCrier -ti bl4ck5un/intel-sgx-sdk-ubuntu-16.04


Alternatively, you can also use `docker run` non-interactively, e.g.:

```shell
# build gtest
docker run -v $(PWD):/home/tc/TownCrier -w "/home/tc/TownCrier/src/utils" bl4ck5un/intel-sgx-sdk-ubuntu-16.04 /bin/sh -c "./build_gtest.sh"

# make everything
docker run -v $(PWD):/home/tc/TownCrier -w "/home/tc/TownCrier/src" bl4ck5un/intel-sgx-sdk-ubuntu-16.04 /bin/sh -c "mkdir -p build; cd build; cmake ..; make; make TestMain"

# run tests
docker run -v $(PWD):/home/tc/TownCrier -w "/home/tc/TownCrier/src/build" bl4ck5un/intel-sgx-sdk-ubuntu-16.04 /bin/sh -c "./TestMain"

# optinally, lint the code
docker run -v $(PWD):/home/tc/TownCrier bl4ck5un/intel-sgx-sdk-ubuntu-16.04 /bin/sh -c "TownCrier/src/lint.sh"
```

See `.travis.yml` for an example of how Docker is used to build and test Town
Crier.

# Prerequisites

This section enumerates the required dependencies to compile Town Crier on your platform.

## Intel Software Guardian eXtension (SGX)

Town Crier makes use of Intel SGX as a trusted execution environment (TEE).
Compiling TC requires libraries provided by the SGX Software Development Kit
(SDK), which is freely available from
[Intel](https://01.org/intel-software-guard-extensions/downloads).  Intel SGX
SDK releases two versions of SGX libraries, a **hardware** version and a
**simulation** version.  The only difference (yet a significant one) is that the
hardware libraries implement SGX APIs with actual SGX hardware instructions
while the simulation libraries just simulate them in the user space. 

TC can be linked against either version of APIs:

- If linked with the hardware libraries, the executable will run in the hardware
  mode, which requires a SGX-enabled CPU.
- If linked with the simulation libraries, the executable will run as if it's an
  ordinary userspace program, providing ABSOLUTELY NO SECURITY GUARANTEE.
  Therefore the simulation mode is only for development and testing purpose.

### Run TC in the simulation mode

To compile and run Town Crier in the simulation mode, one only needs to install
the SGX SDK, which can be obtained from
[here](https://01.org/intel-software-guard-extensions/downloads).

### Run TC in the hardware mode

To run TC on real SGX hardware, some dependency (SGX driver, SGX PSW, SGX SDK)
has to be installed and configured. Please refer to
[linux-sgx](https://github.com/01org/linux-sgx) for instructions.


## Libraries 

- `cmake`: >= 3.0
- `libjsoncpp` 
- [`libjson-rpc-cpp`](https://github.com/cinemast/libjson-rpc-cpp)
- sqlite3: 
- `boost`
- `odb`:
    - odb-2.4.0
    - libodb-2.4.0
    - libodb-sqlite-2.4.0

On Ubuntu 16.04 LTS: 

```
sudo apt-get install cmake libjsoncpp-dev libjsonrpccpp-dev libjsonrpccpp-tools libsqlite3-0 libsqlite3-dev libboost-all-dev libmicrohttpd-dev libcurl4-openssl-dev odb
```

Other platforms have yet to be tested.

# Build

## Build without testing

Build the TLS library first:

```
make -C Enclave/mbedtls-SGX
```

Then build the Town Crier with CMake:

```
mkdir build
cd build
cmake ..
make tc
```

The compiled binary will be `build/tc`.

## Build with Tests (gtest)
----

To build tests, build vendored `gtest` first

```
./utils/build_gtest.sh
```

Then build self tests with CMake the same as building Town Crier

```
mkdir build
cd build
cmake ..
make TestMain
```


After you build and install Town Crier, run `build/TestMain` to test (powered by GTest).



Run
----

A configuration is needed to run tc.

We need to specify RPChost in this configuration.

```
cd build
echo "[RPC]" >> config
echo "RPChost = http://localhost:8200" >> config
./tc config
```

Status Server
-------------

```
curl -d '{"id": 123, "jsonrpc": "2.0", "method": "attest"}' server.town-crier.org:8123
```

# LICENSE

The permission granted herein is solely for the purpose of compiling the TownCrier source code.
See the LICENSE file for details.
