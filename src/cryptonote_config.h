// Copyright (c) 2014-2024, The Monero Project
// 
// All rights reserved.
// 
// Redistribution and use in source and binary forms, with or without modification, are
// permitted provided that the following conditions are met:
// 
// 1. Redistributions of source code must retain the above copyright notice, this list of
//    conditions and the following disclaimer.
// 
// 2. Redistributions in binary form must reproduce the above copyright notice, this list
//    of conditions and the following disclaimer in the documentation and/or other
//    materials provided with the distribution.
// 
// 3. Neither the name of the copyright holder nor the names of its contributors may be
//    used to endorse or promote products derived from this software without specific
//    prior written permission.
// 
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
// MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL
// THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
// STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF
// THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
// 
// Parts of this file are originally copyright (c) 2012-2013 The Cryptonote developers

#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>
#include <boost/uuid/uuid.hpp>

#define CRYPTONOTE_DNS_TIMEOUT_MS                       10000  // Lowered timeout for Arduino

#define CRYPTONOTE_MAX_BLOCK_NUMBER                     10000000   // Smaller maximum block number for a niche network
#define CRYPTONOTE_MAX_TX_SIZE                          500000     // Reduced max transaction size
#define CRYPTONOTE_MAX_TX_PER_BLOCK                     0x100000   // Lowered tx per block limit
#define CRYPTONOTE_PUBLIC_ADDRESS_TEXTBLOB_VER          0
#define CRYPTONOTE_MINED_MONEY_UNLOCK_WINDOW            30         // Faster unlock for coinbase rewards
#define CURRENT_TRANSACTION_VERSION                     1          // Use a simpler transaction version
#define CURRENT_BLOCK_MAJOR_VERSION                     1
#define CURRENT_BLOCK_MINOR_VERSION                     0
#define CRYPTONOTE_BLOCK_FUTURE_TIME_LIMIT              (60*10)    // 10 minutes future time limit
#define CRYPTONOTE_DEFAULT_TX_SPENDABLE_AGE             5          // Faster spendable age

#define BLOCKCHAIN_TIMESTAMP_CHECK_WINDOW               10         // Smaller window for Arduino clocks

// MONEY_SUPPLY - total number coins to be generated
#define MONEY_SUPPLY                                    ((uint64_t)(-1))  // Let the emission curve handle supply
#define EMISSION_SPEED_FACTOR_PER_MINUTE                (10)       // Faster emission (shift right by 10)
#define FINAL_SUBSIDY_PER_MINUTE                        ((uint64_t)100000000000) // Reduced final subsidy

#define CRYPTONOTE_REWARD_BLOCKS_WINDOW                 100
#define CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V2    5000       // Smaller block reward zone (5 KB)
#define CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V1    2000       // Even smaller before fork (2 KB)
#define CRYPTONOTE_BLOCK_GRANTED_FULL_REWARD_ZONE_V5    10000      // Post-fork reward zone (10 KB)
#define CRYPTONOTE_LONG_TERM_BLOCK_WEIGHT_WINDOW_SIZE   5000       // Reduced window for Arduino
#define CRYPTONOTE_SHORT_TERM_BLOCK_WEIGHT_SURGE_FACTOR 10         // Lower surge factor
#define CRYPTONOTE_COINBASE_BLOB_RESERVED_SIZE          300        // Reduced for simpler coinbase transactions
#define CRYPTONOTE_DISPLAY_DECIMAL_POINT                12
// COIN - number of smallest units in one coin
#define COIN                                            ((uint64_t)1000000000000) // 10^12

#define FEE_PER_KB_OLD                                  ((uint64_t)5000000000)  // Lower fees for Arduino
#define FEE_PER_KB                                      ((uint64_t)1000000000)  // Reduced fee per KB
#define FEE_PER_BYTE                                    ((uint64_t)100000)
#define DYNAMIC_FEE_PER_KB_BASE_FEE                     ((uint64_t)1000000000)  // Lower dynamic base fee
#define DYNAMIC_FEE_PER_KB_BASE_BLOCK_REWARD            ((uint64_t)5000000000000) // Lower base reward scaling
#define DYNAMIC_FEE_REFERENCE_TRANSACTION_WEIGHT         ((uint64_t)1500)

#define ORPHANED_BLOCKS_MAX_COUNT                       50         // Fewer orphan blocks

#define DIFFICULTY_TARGET_V2                            180        // 3 minutes target for Arduino-friendly mining
#define DIFFICULTY_TARGET_V1                            120        // 2 minutes for pre-fork version
#define DIFFICULTY_WINDOW                               120        // Smaller window for faster adjustments
#define DIFFICULTY_LAG                                  10         // Reduced lag
#define DIFFICULTY_CUT                                  30         // Fewer timestamps cut
#define DIFFICULTY_BLOCKS_COUNT                         (DIFFICULTY_WINDOW + DIFFICULTY_LAG)

#define CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_SECONDS_V1   (DIFFICULTY_TARGET_V1 * 1)
#define CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_SECONDS_V2   (DIFFICULTY_TARGET_V2 * 1)
#define CRYPTONOTE_LOCKED_TX_ALLOWED_DELTA_BLOCKS       1

#define DIFFICULTY_BLOCKS_ESTIMATE_TIMESPAN             DIFFICULTY_TARGET_V1

#define BLOCKS_IDS_SYNCHRONIZING_DEFAULT_COUNT          1000       // Reduced for Arduino
#define BLOCKS_IDS_SYNCHRONIZING_MAX_COUNT              5000       // Reduced max count
#define BLOCKS_SYNCHRONIZING_DEFAULT_COUNT_PRE_V4       50         // Reduced for Arduino
#define BLOCKS_SYNCHRONIZING_DEFAULT_COUNT              10         // Fewer blocks by default
#define BLOCKS_SYNCHRONIZING_MAX_COUNT                  512        // Power of 2, reduced

#define CRYPTONOTE_MEMPOOL_TX_LIVETIME                    (86400 * 2)  // 2 days lifetime
#define CRYPTONOTE_MEMPOOL_TX_FROM_ALT_BLOCK_LIVETIME     604800       // 1 week

#define CRYPTONOTE_DANDELIONPP_STEMS              2
#define CRYPTONOTE_DANDELIONPP_FLUFF_PROBABILITY 20            // Keep as default
#define CRYPTONOTE_DANDELIONPP_MIN_EPOCH         10
#define CRYPTONOTE_DANDELIONPP_EPOCH_RANGE       30
#define CRYPTONOTE_DANDELIONPP_FLUSH_AVERAGE      5
#define CRYPTONOTE_DANDELIONPP_EMBARGO_AVERAGE   39

#define CRYPTONOTE_NOISE_MIN_EPOCH                      5
#define CRYPTONOTE_NOISE_EPOCH_RANGE                    30
#define CRYPTONOTE_NOISE_MIN_DELAY                      10
#define CRYPTONOTE_NOISE_DELAY_RANGE                    5
#define CRYPTONOTE_NOISE_BYTES                          (3 * 1024)
#define CRYPTONOTE_NOISE_CHANNELS                       2

#define CRYPTONOTE_FORWARD_DELAY_BASE                   (10 + 5)   // noise min delay + range
#define CRYPTONOTE_FORWARD_DELAY_AVERAGE                (15 + (15 / 2))

#define CRYPTONOTE_MAX_FRAGMENTS                        20

#define COMMAND_RPC_GET_BLOCKS_FAST_MAX_BLOCK_COUNT     500        // Lowered for Arduino
#define COMMAND_RPC_GET_BLOCKS_FAST_MAX_TX_COUNT        10000      // Lowered for Arduino
#define DEFAULT_RPC_MAX_CONNECTIONS_PER_PUBLIC_IP       2
#define DEFAULT_RPC_MAX_CONNECTIONS_PER_PRIVATE_IP      10
#define DEFAULT_RPC_MAX_CONNECTIONS                     50
#define DEFAULT_RPC_SOFT_LIMIT_SIZE                     (15 * 1024 * 1024) // 15 MiB
#define MAX_RPC_CONTENT_LENGTH                          524288     // 512 KB

#define P2P_LOCAL_WHITE_PEERLIST_LIMIT                  500
#define P2P_LOCAL_GRAY_PEERLIST_LIMIT                   1000

#define P2P_DEFAULT_CONNECTIONS_COUNT                   8
#define P2P_DEFAULT_HANDSHAKE_INTERVAL                  60
#define P2P_DEFAULT_PACKET_MAX_SIZE                     5000000    // Reduced packet size
#define P2P_DEFAULT_PEERS_IN_HANDSHAKE                  100
#define P2P_MAX_PEERS_IN_HANDSHAKE                      100
#define P2P_DEFAULT_CONNECTION_TIMEOUT                  5000
#define P2P_DEFAULT_SOCKS_CONNECT_TIMEOUT               45
#define P2P_DEFAULT_PING_CONNECTION_TIMEOUT             2000
#define P2P_DEFAULT_INVOKE_TIMEOUT                      (60 * 2 * 1000)
#define P2P_DEFAULT_HANDSHAKE_INVOKE_TIMEOUT            5000
#define P2P_DEFAULT_WHITELIST_CONNECTIONS_PERCENT       50
#define P2P_DEFAULT_ANCHOR_CONNECTIONS_COUNT            1
#define P2P_DEFAULT_SYNC_SEARCH_CONNECTIONS_COUNT       1
#define P2P_DEFAULT_LIMIT_RATE_UP                       1024       // kB/s
#define P2P_DEFAULT_LIMIT_RATE_DOWN                     8192       // kB/s

#define P2P_FAILED_ADDR_FORGET_SECONDS                  (60 * 60)
#define P2P_IP_BLOCKTIME                                (60 * 60 * 24)
#define P2P_IP_FAILS_BEFORE_BLOCK                       10
#define P2P_IDLE_CONNECTION_KILL_INTERVAL               (5 * 60)

#define P2P_SUPPORT_FLAG_FLUFFY_BLOCKS                  0x01
#define P2P_SUPPORT_FLAGS                               P2P_SUPPORT_FLAG_FLUFFY_BLOCKS

#define RPC_IP_FAILS_BEFORE_BLOCK                       3

#define CRYPTONOTE_NAME                                 "zone"
#define CRYPTONOTE_BLOCKCHAINDATA_FILENAME              "data.mdb"
#define CRYPTONOTE_BLOCKCHAINDATA_LOCK_FILENAME         "lock.mdb"
#define P2P_NET_DATA_FILENAME                           "p2pstate.bin"
#define RPC_PAYMENTS_DATA_FILENAME                      "rpcpayments.bin"
#define MINER_CONFIG_FILE_NAME                          "miner_conf.json"

#define THREAD_STACK_SIZE                               (2 * 1024 * 1024) // Reduced stack for Arduino

#define HF_VERSION_DYNAMIC_FEE                          4
#define HF_VERSION_MIN_MIXIN_4                          6
#define HF_VERSION_MIN_MIXIN_6                          7
#define HF_VERSION_MIN_MIXIN_10                         8
#define HF_VERSION_MIN_MIXIN_15                         10
#define HF_VERSION_ENFORCE_RCT                          6
#define HF_VERSION_PER_BYTE_FEE                         8
#define HF_VERSION_SMALLER_BP                           10
#define HF_VERSION_LONG_TERM_BLOCK_WEIGHT               10
#define HF_VERSION_MIN_2_OUTPUTS                        12
#define HF_VERSION_MIN_V2_COINBASE_TX                   12
#define HF_VERSION_SAME_MIXIN                           12
#define HF_VERSION_REJECT_SIGS_IN_COINBASE              12
#define HF_VERSION_ENFORCE_MIN_AGE                      12
#define HF_VERSION_EFFECTIVE_SHORT_TERM_MEDIAN_IN_PENALTY 12
#define HF_VERSION_EXACT_COINBASE                       13
#define HF_VERSION_CLSAG                                13
#define HF_VERSION_DETERMINISTIC_UNLOCK_TIME            13
#define HF_VERSION_BULLETPROOF_PLUS                     15
#define HF_VERSION_VIEW_TAGS                            15
#define HF_VERSION_2021_SCALING                         15

#define PER_KB_FEE_QUANTIZATION_DECIMALS                8
#define CRYPTONOTE_SCALING_2021_FEE_ROUNDING_PLACES       2

#define HASH_OF_HASHES_STEP                             512

#define DEFAULT_TXPOOL_MAX_WEIGHT                       324000000ull  // Reduced for Arduino (half of previous)
#define BULLETPROOF_MAX_OUTPUTS                         16
#define BULLETPROOF_PLUS_MAX_OUTPUTS                    16

#define CRYPTONOTE_PRUNING_STRIPE_SIZE                  4096
#define CRYPTONOTE_PRUNING_LOG_STRIPES                  3
#define CRYPTONOTE_PRUNING_TIP_BLOCKS                   5500

#define RPC_CREDITS_PER_HASH_SCALE                      ((float)(1<<24))

#define DNS_BLOCKLIST_LIFETIME                          (86400 * 8)

#define MAX_TX_EXTRA_SIZE                               1060

namespace config
{
  uint64_t const DEFAULT_FEE_ATOMIC_XMR_PER_KB = 200; // Lower fee for Arduino
  uint8_t const FEE_CALCULATION_MAX_RETRIES = 5;
  uint64_t const DEFAULT_DUST_THRESHOLD = ((uint64_t)1000000000); // Lower dust threshold
  uint64_t const BASE_REWARD_CLAMP_THRESHOLD = ((uint64_t)100000000); 

  uint64_t const CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX = 18;
  uint64_t const CRYPTONOTE_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX = 19;
  uint64_t const CRYPTONOTE_PUBLIC_SUBADDRESS_BASE58_PREFIX = 42;
  uint16_t const P2P_DEFAULT_PORT = 18080;
  uint16_t const RPC_DEFAULT_PORT = 18081;
  uint16_t const ZMQ_RPC_DEFAULT_PORT = 18082;
  boost::uuids::uuid const NETWORK_ID = { {
      0x12, 0x30, 0xF1, 0x71, 0x61, 0x04, 0x41, 0x61, 0x17, 0x31, 0x00, 0x82, 0x16, 0xA1, 0xA1, 0x10
    } };
  std::string const GENESIS_TX = "013c01ff0001ffffffffffff03029b2e4c0281c0b02e7c53291a94d1d0cbff8883f8024f5142ee494ffbbd08807121017767aafcde9be00dcfd098715ebcf7f410daebc582fda69d24a28a9d0bc890d1";
  uint32_t const GENESIS_NONCE = 10000;

  const char HASH_KEY_BULLETPROOF_EXPONENT[] = "bulletproof";
  const char HASH_KEY_BULLETPROOF_PLUS_EXPONENT[] = "bulletproof_plus";
  const char HASH_KEY_BULLETPROOF_PLUS_TRANSCRIPT[] = "bulletproof_plus_transcript";
  const char HASH_KEY_RINGDB[] = "ringdsb";
  const char HASH_KEY_SUBADDRESS[] = "SubAddr";
  const unsigned char HASH_KEY_ENCRYPTED_PAYMENT_ID = 0x8d;
  const unsigned char HASH_KEY_WALLET = 0x8c;
  const unsigned char HASH_KEY_WALLET_CACHE = 0x8d;
  const unsigned char HASH_KEY_BACKGROUND_CACHE = 0x8e;
  const unsigned char HASH_KEY_BACKGROUND_KEYS_FILE = 0x8f;
  const unsigned char HASH_KEY_RPC_PAYMENT_NONCE = 0x58;
  const unsigned char HASH_KEY_MEMORY = 'k';
  const unsigned char HASH_KEY_MULTISIG[] = { 'M','u','l','t','i','s','i','g', 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
  const unsigned char HASH_KEY_MULTISIG_KEY_AGGREGATION[] = "Multisig_key_agg";
  const unsigned char HASH_KEY_CLSAG_ROUND_MULTISIG[] = "CLSAG_round_ms_merge_factor";
  const unsigned char HASH_KEY_TXPROOF_V2[] = "TXPROOF_V2";
  const unsigned char HASH_KEY_CLSAG_ROUND[] = "CLSAG_round";
  const unsigned char HASH_KEY_CLSAG_AGG_0[] = "CLSAG_agg_0";
  const unsigned char HASH_KEY_CLSAG_AGG_1[] = "CLSAG_agg_1";
  const char HASH_KEY_MESSAGE_SIGNING[] = "MoneroMessageSignature";
  const unsigned char HASH_KEY_MM_SLOT = 'm';
  const constexpr char HASH_KEY_MULTISIG_TX_PRIVKEYS_SEED[] = "multisig_tx_privkeys_seed";
  const constexpr char HASH_KEY_MULTISIG_TX_PRIVKEYS[] = "multisig_tx_privkeys";
  const constexpr char HASH_KEY_TXHASH_AND_MIXRING[] = "txhash_and_mixring";

  const uint32_t MULTISIG_MAX_SIGNERS{16};

  namespace testnet
  {
    uint64_t const CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX = 53;
    uint64_t const CRYPTONOTE_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX = 54;
    uint64_t const CRYPTONOTE_PUBLIC_SUBADDRESS_BASE58_PREFIX = 63;
    uint16_t const P2P_DEFAULT_PORT = 28080;
    uint16_t const RPC_DEFAULT_PORT = 28081;
    uint16_t const ZMQ_RPC_DEFAULT_PORT = 28082;
    boost::uuids::uuid const NETWORK_ID = { {
        0x12, 0x30, 0xF1, 0x71, 0x61, 0x04, 0x41, 0x61, 0x17, 0x31, 0x00, 0x82, 0x16, 0xA1, 0xA1, 0x11
      } };
    std::string const GENESIS_TX = "013c01ff0001ffffffffffff03029b2e4c0281c0b02e7c53291a94d1d0cbff8883f8024f5142ee494ffbbd08807121017767aafcde9be00dcfd098715ebcf7f410daebc582fda69d24a28a9d0bc890d1";
    uint32_t const GENESIS_NONCE = 10001;
  }

  namespace stagenet
  {
    uint64_t const CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX = 24;
    uint64_t const CRYPTONOTE_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX = 25;
    uint64_t const CRYPTONOTE_PUBLIC_SUBADDRESS_BASE58_PREFIX = 36;
    uint16_t const P2P_DEFAULT_PORT = 38080;
    uint16_t const RPC_DEFAULT_PORT = 38081;
    uint16_t const ZMQ_RPC_DEFAULT_PORT = 38082;
    boost::uuids::uuid const NETWORK_ID = { {
        0x12, 0x30, 0xF1, 0x71, 0x61, 0x04, 0x41, 0x61, 0x17, 0x31, 0x00, 0x82, 0x16, 0xA1, 0xA1, 0x12
      } };
    std::string const GENESIS_TX = "013c01ff0001ffffffffffff0302df5d56da0c7d643ddd1ce61901c7bdc5fb1738bfe39fbe69c28a3a7032729c0f2101168d0c4ca86fb55a4cf6a36d31431be1c53a3bd7411bb24e8832410289fa6f3b";
    uint32_t const GENESIS_NONCE = 10002;
  }
}

namespace cryptonote
{
  enum network_type : uint8_t
  {
    MAINNET = 0,
    TESTNET,
    STAGENET,
    FAKECHAIN,
    UNDEFINED = 255
  };
  struct config_t
  {
    uint64_t const CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX;
    uint64_t const CRYPTONOTE_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX;
    uint64_t const CRYPTONOTE_PUBLIC_SUBADDRESS_BASE58_PREFIX;
    uint16_t const P2P_DEFAULT_PORT;
    uint16_t const RPC_DEFAULT_PORT;
    uint16_t const ZMQ_RPC_DEFAULT_PORT;
    boost::uuids::uuid const NETWORK_ID;
    std::string const GENESIS_TX;
    uint32_t const GENESIS_NONCE;
  };
  inline const config_t& get_config(network_type nettype)
  {
    static const config_t mainnet = {
      ::config::CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX,
      ::config::CRYPTONOTE_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX,
      ::config::CRYPTONOTE_PUBLIC_SUBADDRESS_BASE58_PREFIX,
      ::config::P2P_DEFAULT_PORT,
      ::config::RPC_DEFAULT_PORT,
      ::config::ZMQ_RPC_DEFAULT_PORT,
      ::config::NETWORK_ID,
      ::config::GENESIS_TX,
      ::config::GENESIS_NONCE
    };
    static const config_t testnet = {
      ::config::testnet::CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX,
      ::config::testnet::CRYPTONOTE_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX,
      ::config::testnet::CRYPTONOTE_PUBLIC_SUBADDRESS_BASE58_PREFIX,
      ::config::testnet::P2P_DEFAULT_PORT,
      ::config::testnet::RPC_DEFAULT_PORT,
      ::config::testnet::ZMQ_RPC_DEFAULT_PORT,
      ::config::testnet::NETWORK_ID,
      ::config::testnet::GENESIS_TX,
      ::config::testnet::GENESIS_NONCE
    };
    static const config_t stagenet = {
      ::config::stagenet::CRYPTONOTE_PUBLIC_ADDRESS_BASE58_PREFIX,
      ::config::stagenet::CRYPTONOTE_PUBLIC_INTEGRATED_ADDRESS_BASE58_PREFIX,
      ::config::stagenet::CRYPTONOTE_PUBLIC_SUBADDRESS_BASE58_PREFIX,
      ::config::stagenet::P2P_DEFAULT_PORT,
      ::config::stagenet::RPC_DEFAULT_PORT,
      ::config::stagenet::ZMQ_RPC_DEFAULT_PORT,
      ::config::stagenet::NETWORK_ID,
      ::config::stagenet::GENESIS_TX,
      ::config::stagenet::GENESIS_NONCE
    };
    switch (nettype)
    {
      case MAINNET: return mainnet;
      case TESTNET: return testnet;
      case STAGENET: return stagenet;
      case FAKECHAIN: return mainnet;
      default: throw std::runtime_error("Invalid network type");
    }
  };
}
