#!/bin/sh
#
# Copyright (c) 2016-2017 by Cornell University.  All Rights Reserved.
#
# Permission to use the "TownCrier" software ("TownCrier"), officially
# docketed at the Center for Technology Licensing at Cornell University
# as D-7364, developed through research conducted at Cornell University,
# and its associated copyrights solely for educational, research and
# non-profit purposes without fee is hereby granted, provided that the
# user agrees as follows:
#
# The permission granted herein is solely for the purpose of compiling
# the TowCrier source code. No other rights to use TownCrier and its
# associated copyrights for any other purpose are granted herein,
# whether commercial or non-commercial.
#
# Those desiring to incorporate TownCrier software into commercial
# products or use TownCrier and its associated copyrights for commercial
# purposes must contact the Center for Technology Licensing at Cornell
# University at 395 Pine Tree Road, Suite 310, Ithaca, NY 14850; email:
# ctl-connect@cornell.edu; Tel: 607-254-4698; FAX: 607-254-5454 for a
# commercial license.
#
# IN NO EVENT SHALL CORNELL UNIVERSITY BE LIABLE TO ANY PARTY FOR
# DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES,
# INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF TOWNCRIER AND ITS
# ASSOCIATED COPYRIGHTS, EVEN IF CORNELL UNIVERSITY MAY HAVE BEEN
# ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# THE WORK PROVIDED HEREIN IS ON AN "AS IS" BASIS, AND CORNELL
# UNIVERSITY HAS NO OBLIGATION TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
# ENHANCEMENTS, OR MODIFICATIONS.  CORNELL UNIVERSITY MAKES NO
# REPRESENTATIONS AND EXTENDS NO WARRANTIES OF ANY KIND, EITHER IMPLIED
# OR EXPRESS, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
# MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, OR THAT THE USE
# OF TOWNCRIER AND ITS ASSOCIATED COPYRIGHTS WILL NOT INFRINGE ANY
# PATENT, TRADEMARK OR OTHER RIGHTS.
#
# TownCrier was developed with funding in part by the National Science
# Foundation (NSF grants CNS-1314857, CNS-1330599, CNS-1453634,
# CNS-1518765, CNS-1514261), a Packard Fellowship, a Sloan Fellowship,
# Google Faculty Research Awards, and a VMWare Research Award.
#
# Measure memory usage of a minimal client using a small configuration
# Currently hardwired to ccm-psk and suite-b, may be expanded later
#
# Use different build options for measuring executable size and memory usage,
# since for memory we want debug information.

set -eu

CONFIG_H='include/mbedtls/config.h'

CLIENT='mini_client'

CFLAGS_EXEC='-fno-asynchronous-unwind-tables -Wl,--gc-section -ffunction-sections -fdata-sections'
CFLAGS_MEM=-g3

if [ -r $CONFIG_H ]; then :; else
    echo "$CONFIG_H not found" >&2
    exit 1
fi

if grep -i cmake Makefile >/dev/null; then
    echo "Not compatible with CMake" >&2
    exit 1
fi

if [ $( uname ) != Linux ]; then
    echo "Only work on Linux" >&2
    exit 1
fi

if git status | grep -F $CONFIG_H >/dev/null 2>&1; then
    echo "config.h not clean" >&2
    exit 1
fi

# make measurements with one configuration
# usage: do_config <name> <unset-list> <server-args>
do_config()
{
    NAME=$1
    UNSET_LIST=$2
    SERVER_ARGS=$3

    echo ""
    echo "config-$NAME:"
    cp configs/config-$NAME.h $CONFIG_H
    scripts/config.pl unset MBEDTLS_SSL_SRV_C

    for FLAG in $UNSET_LIST; do
        scripts/config.pl unset $FLAG
    done

    grep -F SSL_MAX_CONTENT_LEN $CONFIG_H || echo 'SSL_MAX_CONTENT_LEN=16384'

    printf "    Executable size... "

    make clean
    CFLAGS=$CFLAGS_EXEC make OFLAGS=-Os lib >/dev/null 2>&1
    cd programs
    CFLAGS=$CFLAGS_EXEC make OFLAGS=-Os ssl/$CLIENT >/dev/null
    strip ssl/$CLIENT
    stat -c '%s' ssl/$CLIENT
    cd ..

    printf "    Peak ram usage... "

    make clean
    CFLAGS=$CFLAGS_MEM make OFLAGS=-Os lib >/dev/null 2>&1
    cd programs
    CFLAGS=$CFLAGS_MEM make OFLAGS=-Os ssl/$CLIENT >/dev/null
    cd ..

    ./ssl_server2 $SERVER_ARGS >/dev/null &
    SRV_PID=$!
    sleep 1;

    if valgrind --tool=massif --stacks=yes programs/ssl/$CLIENT >/dev/null 2>&1
    then
        FAILED=0
    else
        echo "client failed" >&2
        FAILED=1
    fi

    kill $SRV_PID
    wait $SRV_PID

    scripts/massif_max.pl massif.out.*
    mv massif.out.* massif-$NAME.$$
}

# preparation

CONFIG_BAK=${CONFIG_H}.bak
cp $CONFIG_H $CONFIG_BAK

rm -f massif.out.*

printf "building server... "

make clean
make lib >/dev/null 2>&1
(cd programs && make ssl/ssl_server2) >/dev/null
cp programs/ssl/ssl_server2 .

echo "done"

# actual measurements

do_config   "ccm-psk-tls1_2" \
            "" \
            "psk=000102030405060708090A0B0C0D0E0F"

do_config   "suite-b" \
            "MBEDTLS_BASE64_C MBEDTLS_PEM_PARSE_C MBEDTLS_CERTS_C" \
            ""

# cleanup

mv $CONFIG_BAK $CONFIG_H
make clean
rm ssl_server2

exit $FAILED