#include <gtest/gtest.h>
#include "Debug.h"
#include "../Init.h"
#include "../Enclave_u.h"
#include "../Utils.h"
#include "../../Common/Constants.h"

TEST (EventHandler, Steam) {
    sgx_enclave_id_t eid;
    sgx_status_t ecall_ret;
    int ret = initialize_enclave(ENCLAVE_FILENAME, &eid);
    ASSERT_EQ(SGX_SUCCESS, ret);

    uint8_t data[] = {246,141,42,50,207,23,177,49,44,109,179,242,54,163,140,148,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,76,159,146,246,236,30,42,32,161,65,61,10,193,184,103,163,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,31,92,131,160,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,60,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,80,111,114,116,97,108,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    uint8_t tx[2048];
  size_t tx_len;
    ecall_ret = handle_request(eid, &ret, 0, 1, 2, data, 192, tx, &tx_len);
    ASSERT_EQ(SGX_SUCCESS, ecall_ret);
    ASSERT_EQ(0, ret);
    ASSERT_EQ(204, tx_len);
    uint8_t ans[] = {248,202,128,133,11,164,59,116,0,131,1,95,144,148,224,226,128,88,83,118,192,183,32,174,171,151,88,133,251,173,90,196,230,206,128,184,100,176,112,185,186,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,18,120,47,194,110,22,175,204,97,158,123,124,230,84,174,112,89,153,10,80,130,49,109,143,251,41,135,225,230,105,64,202,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,28,160,100,139,184,205,211,104,40,93,108,235,165,83,49,167,137,40,20,180,0,61,186,217,101,93,193,147,66,110,209,120,73,64,160,23,49,175,80,149,53,112,128,212,2,155,224,234,17,92,124,11,174,121,19,173,71,191,160,127,158,175,182,64,117,244,19};


    std::vector<uint8_t> tcAddress;
    fromHex(TC_ADDRESS, tcAddress);

    for (auto i = 14; i < 14 + 20; i++)
    {
        ans[i] = tcAddress.at(i-14);
    }

    if (memcmp(tx, ans, 136)) {
        LL_CRITICAL("memcmp failed");
        hexdump("correct:", ans, 136);
        hexdump("Ours: ", tx, 136);
    }
}
