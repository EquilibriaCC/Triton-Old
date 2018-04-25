/*
 * Copyright (c) 2017-2018, The Alloy Developers.
 * Portions Copyright (c) 2012-2017, The CryptoNote Developers, The Bytecoin Developers.
 *
 * This file is part of Alloy.
 *
 * This file is subject to the terms and conditions defined in the
 * file 'LICENSE', which is part of this source code package.
 */

#pragma once

#include <cstddef>
#include <cstdint>
#include <limits>
#include <initializer_list>

namespace CryptoNote {
namespace parameters {

#define CRYPTONOTE_MAX_BLOCK_NUMBER                     500000000
#define CRYPTONOTE_MAX_BLOCK_BLOB_SIZE                  500000000
#define CRYPTONOTE_MAX_TX_SIZE                          1000000000
#define CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX         289 // starts with "T"
#define CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW            30
#define CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT              60 * 60 * 2

#define BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW               60

#define MONEY_SUPPLY                                    84000000
#define MIN_MIXIN                                       0
#define MANDATORY_MIXIN_BLOCK_VERSION                   0
#define KILL_HEIGHT                                     0
#define ZAWY_DIFFICULTY_BLOCK_INDEX                     0
#define ZAWY_DIFFICULTY_V2                              1
#define ZAWY_DIFFICULTY_DIFFICULTY_BLOCK_VERSION        0
#define EMISSION_SPEED_FACTOR                           20
#define GENESIS_BLOCK_REWARD                            3000000

#define CRYPTONOTE_REWARD_BLOCKS_WINDOW                 100
#define CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE       100000
#define CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V2    90000
#define CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1    80000
#define CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_CURRENT CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE
#define CRYPTONOTE_COINBASE_BLOB_RESERVED_SIZE          600
#define CRYPTONOTE_MONEY_DECIMAL_POINT                  12
#define CRYPTONOTE_MONEY_DECIMAL_UNITS                  (uint64_t)pow(10, CRYPTONOTE_MONEY_DECIMAL_POINT)
#define MINIMUM_FEE                                     (uint64_t)pow(10, CRYPTONOTE_MONEY_DECIMAL_POINT / 2)
#define DEFAULT_FEE                                     (uint64_t)pow(10, CRYPTONOTE_MONEY_DECIMAL_POINT - 2)
#define DEFAULT_DUST_THRESHOLD                          MINIMUM_FEE

#define TX_SAFETY_NET					                20000 // upper safety net to prevent stuck transactions
#define MAX_TRANSACTION_SIZE_LIMIT                      CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE / 4 - CRYPTONOTE_COINBASE_BLOB_RESERVED_SIZE

#define DIFFICULTY_TARGET                               180
#define EXPECTED_NUMBER_OF_BLOCKS_PER_DAY               24 * 60 * 60 / DIFFICULTY_TARGET
#define DIFFICULTY_WINDOW                               EXPECTED_NUMBER_OF_BLOCKS_PER_DAY
#define DIFFICULTY_WINDOW_V1                            DIFFICULTY_WINDOW
#define DIFFICULTY_WINDOW_V2                            DIFFICULTY_WINDOW
#define DIFFICULTY_CUT                                  60
#define DIFFICULTY_CUT_V1                               DIFFICULTY_CUT
#define DIFFICULTY_CUT_V2                               DIFFICULTY_CUT
#define DIFFICULTY_LAG                                  15
#define DIFFICULTY_LAG_V1                               DIFFICULTY_LAG
#define DIFFICULTY_LAG_V2                               DIFFICULTY_LAG

#define MAX_BLOCK_SIZE_INITIAL                          100 * 1024
#define MAX_BLOCK_SIZE_GROWTH_SPEED_NUMERATOR           100 * 1024
#define MAX_BLOCK_SIZE_GROWTH_SPEED_DENOMINATOR         365 * 24 * 60 * 60 / DIFFICULTY_TARGET

#define CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS       1
#define CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_SECONDS      DIFFICULTY_TARGET * CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS

#define CRYPTONOTE_MEMPOOL_TX_LIVETIME                  60 * 60 * 6
#define CRYPTONOTE_MEMPOOL_TX_FROM_ALT_BLOCK_LIVETIME   CRYPTONOTE_MEMPOOL_TX_LIVETIME * 7
#define CRYPTONOTE_NUMBER_OF_PERIODS_TO_FORGET_TX_DELETED_FROM_POOL 7

#define FUSION_TX_MAX_SIZE                              MAX_TRANSACTION_SIZE_LIMIT * 2
#define FUSION_TX_MIN_INPUT_COUNT                       12
#define FUSION_TX_MIN_IN_OUT_COUNT_RATIO                4

#define KEY_IMAGE_CHECKING_BLOCK_INDEX                  0
#define UPGRADE_HEIGHT_V2                               1
#define UPGRADE_HEIGHT_V3                               2
#define UPGRADE_HEIGHT_V4                               24830
#define UPGRADE_VOTING_THRESHOLD                        90
#define UPGRADE_VOTING_WINDOW                           EXPECTED_NUMBER_OF_BLOCKS_PER_DAY
#define UPGRADE_WINDOW                                  EXPECTED_NUMBER_OF_BLOCKS_PER_DAY

#define CRYPTONOTE_BLOCKS_FILENAME                      "blocks.bin"
#define CRYPTONOTE_BLOCKINDEXES_FILENAME                "blockindexes.bin"
#define CRYPTONOTE_POOLDATA_FILENAME                    "poolstate.bin"
#define P2P_NET_DATA_FILENAME                           "p2pstate.bin"
#define MINER_CONFIG_FILE_NAME                          "miner_conf.json"

} // parameters

#define CRYPTONOTE_NAME                                 "Triton"
#define CRYPTONOTE_GENESIS_TX                           "011e01ff0001c08db7010230e5cf1935ea03354beeecdfd94b46d425d1e0b85333edd4f99cdfde6c65adea21012569ed651af1f16d3c49ecafb944db6a6f78ba5977f594678ff891f0bdb80354"

#define TRANSACTION_VERSION_1                           1
#define TRANSACTION_VERSION_2                           2
#define CURRENT_TRANSACTION_VERSION                     TRANSACTION_VERSION_1
#define BLOCK_MAJOR_VERSION_1                           1
#define BLOCK_MAJOR_VERSION_2                           2
#define BLOCK_MAJOR_VERSION_3                           3
#define BLOCK_MAJOR_VERSION_4                           4
#define BLOCK_MINOR_VERSION_0                           0
#define BLOCK_MINOR_VERSION_1                           1

#define BLOCKS_IDS_SYNCHRONIZING_DEFAULT_COUNT          10000
#define BLOCKS_SYNCHRONIZING_DEFAULT_COUNT              128
#define COMMAND_RPC_GET_BLOCKS_FAST_MAX_COUNT           1000

#define P2P_DEFAULT_PORT                                9730
#define RPC_DEFAULT_PORT                                9731

#define P2P_LOCAL_WHITE_PEERLIST_LIMIT                  1000
#define P2P_LOCAL_GRAY_PEERLIST_LIMIT                   5000

#define P2P_CONNECTION_MAX_WRITE_BUFFER_SIZE            64 * 1024 * 1024
#define P2P_DEFAULT_CONNECTIONS_COUNT                   8
#define P2P_DEFAULT_WHITELIST_CONNECTIONS_PERCENT       70
#define P2P_DEFAULT_HANDSHAKE_INTERVAL                  60
#define P2P_DEFAULT_PACKET_MAX_SIZE                     50000000
#define P2P_DEFAULT_PEERS_IN_HANDSHAKE                  250
#define P2P_DEFAULT_CONNECTION_TIMEOUT                  5000
#define P2P_DEFAULT_PING_CONNECTION_TIMEOUT             2000
#define P2P_DEFAULT_INVOKE_TIMEOUT                      60 * 2 * 1000
#define P2P_DEFAULT_HANDSHAKE_INVOKE_TIMEOUT            5000
#define P2P_STAT_TRUSTED_PUB_KEY                        "8f80f23dsa434a9f15123dsfd133362423402f32312sad9c918ce505efe225d8c94d045fa115"

const std::initializer_list<const char*> SEED_NODES {
  "93.188.161.244:9730",//us
  "165.227.99.38:9730",//us
  "165.227.125.101:9730",//us
  "178.62.5.221:9730", //eu
  "128.199.165.75:9730"//as
};

struct CheckpointData {
  uint32_t index;
  const char* blockId;
};

#ifdef __GNUC__
__attribute__((unused))
#endif

const std::initializer_list<CheckpointData> CHECKPOINTS {
  { 1, "61fab02c04d60d6c9904dab46250a9e6d360f4724107bc83e7d63dfd9929b9df" },
  { 500, "924ae6502ecaa9ba512c95faf1e476dcffbea6181539a82c76306b68f187e712" },
  { 1000, "ccdc4ce7eb6ada472b042c6dfb08f37710c9902551c8d462143837d430f401ec" },
  { 2000, "8febec9eeba46cc5114f4a2dc3305a0b132f78f563ba8478d855f46ab1a4d1cf" },
  { 4000, "40f33655627768c7ffcfadffb30c9fe098b4828f01c7f9768a83c7be55783993" },
  { 5000, "181805c8667f1d21486aa725789dacaa24208f1d25d14b5101374badf3279f86" },
  { 6000, "49075b66fd5b059e65e641bcb79343a29ecce3349cfce92c3f49623a3b6154f3" },
  { 8000, "220737791dc500ef0626b983bc72b9500d9343ea80863c4acdeb7424d8bf7de4" },
  { 10000, "5ad571fee69a537387721bd7140e45420c28cd5771c7ecc91147021d4355ce60" },
  { 12000, "41d93064f03b2b67a1354d71f51c9457580b40ff4f338a13d98a1910f74e929e" },
  { 14000, "3fd5793ba60c5ae9cd0f8885f52b4d61bca5842f9449a4ece3e1fb00ae4c1619" },
  { 16000, "202ba4eaf3fe024239999977aeb66fab507829cf6c6500000574e14c78bb74e7" },
  { 17000, "1e86b392739ebce1c3796512219627c7da3e3a3f35cc87a24d46f5c4566b5eaf" },
  { 18000, "b7fe8dc973f7cf8d6774f97949753a32c1f79a60a62f8bfa000884a27d5d4f26" },
  { 19000, "aad805a34eb4441b95c1d681ad69a88555497194e84178e643f903a92f5da332" },
  { 20000, "317715723300de19864e308b282f79d467981cfed56aa0542b7e5dbb8857bdfa" },
  { 21000, "7070666766e6003373470dce894dd2ebc490993154f4527bc3601e375853004c" },
  { 22000, "e216b479570e939b588512cfb2fcd6dab19c6f9225781942255b8371b48cc3c1" },
  { 23000, "458429c052ad56b51b4bdbc75543518b718e27f5867495a4cadb638743e433ea" },
  { 24000, "9bb34039cca0d2eab3af512545ca8fba88b261565275269c810930006cd3b914" },



  
  
  
 
};

} // CryptoNote

#define ALLOW_DEBUG_COMMANDS
