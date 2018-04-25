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
#include "Chaingen.h"
#include "TransactionBuilder.h"

const size_t invalid_index_value = std::numeric_limits<size_t>::max();

template <class concrete_test> class gen_double_spend_base : public test_chain_unit_base {
public:
  static const uint64_t send_amount = MK_COINS(17);

  gen_double_spend_base();

  bool check_tx_verification_context(bool tve, bool tx_added, size_t event_idx, const CryptoNote::Transaction& tx);
  bool check_block_verification_context(std::error_code bve, size_t event_idx, const CryptoNote::BlockTemplate& block);
  bool check_block_verification_context(std::error_code bve, size_t event_idx, const CryptoNote::RawBlock& block);

  bool mark_last_valid_block(CryptoNote::Core& c, size_t ev_index, const std::vector<test_event_entry>& events);
  bool mark_invalid_tx(CryptoNote::Core& c, size_t ev_index, const std::vector<test_event_entry>& events);
  bool mark_invalid_block(CryptoNote::Core& c, size_t ev_index, const std::vector<test_event_entry>& events);
  bool check_double_spend(CryptoNote::Core& c, size_t ev_index, const std::vector<test_event_entry>& events);

private:
  CryptoNote::BlockTemplate m_last_valid_block;
  size_t m_invalid_tx_index;
  size_t m_invalid_block_index;
};

template <bool txs_keeped_by_block>
struct gen_double_spend_in_tx : public gen_double_spend_base<gen_double_spend_in_tx<txs_keeped_by_block>> {
  static const uint64_t send_amount = MK_COINS(17);
  static const bool has_invalid_tx = true;
  static const size_t expected_pool_txs_count = 0;
  static const uint64_t expected_bob_balance = send_amount;
  static const uint64_t expected_alice_balance = 0;

  bool generate(std::vector<test_event_entry>& events) const;
};

template <bool txs_keeped_by_block>
struct gen_double_spend_in_the_same_block
    : public gen_double_spend_base<gen_double_spend_in_the_same_block<txs_keeped_by_block>> {
  static const uint64_t send_amount = MK_COINS(17);
  static const bool has_invalid_tx = !txs_keeped_by_block;
  static const size_t expected_pool_txs_count = has_invalid_tx ? 1 : 2;
  static const uint64_t expected_bob_balance = send_amount;
  static const uint64_t expected_alice_balance = 0;

  bool generate(std::vector<test_event_entry>& events) const;
};

template <bool txs_keeped_by_block>
struct gen_double_spend_in_different_blocks
    : public gen_double_spend_base<gen_double_spend_in_different_blocks<txs_keeped_by_block>> {
  static const uint64_t send_amount = MK_COINS(17);
  static const bool has_invalid_tx = !txs_keeped_by_block;
  static const size_t expected_pool_txs_count = has_invalid_tx ? 0 : 1;
  static const uint64_t expected_bob_balance = 0;
  static uint64_t expected_alice_balance;

  gen_double_spend_in_different_blocks()
      : gen_double_spend_base<gen_double_spend_in_different_blocks<txs_keeped_by_block>>() {
    expected_alice_balance = send_amount - this->m_currency->minimumFee();
  }

  bool generate(std::vector<test_event_entry>& events) const;
};

template <bool txs_keeped_by_block>
uint64_t gen_double_spend_in_different_blocks<txs_keeped_by_block>::expected_alice_balance;

template <bool txs_keeped_by_block>
struct gen_double_spend_in_alt_chain_in_the_same_block
    : public gen_double_spend_base<gen_double_spend_in_alt_chain_in_the_same_block<txs_keeped_by_block>> {
  static const uint64_t send_amount = MK_COINS(17);
  static const bool has_invalid_tx = !txs_keeped_by_block;
  static const size_t expected_pool_txs_count = has_invalid_tx ? 1 : 2;
  static const uint64_t expected_bob_balance = send_amount;
  static const uint64_t expected_alice_balance = 0;

  bool generate(std::vector<test_event_entry>& events) const;
};

template <bool txs_keeped_by_block>
struct gen_double_spend_in_alt_chain_in_different_blocks
    : public gen_double_spend_base<gen_double_spend_in_alt_chain_in_different_blocks<txs_keeped_by_block>> {
  static const uint64_t send_amount = MK_COINS(17);
  static const bool has_invalid_tx = !txs_keeped_by_block;
  static const size_t expected_pool_txs_count = has_invalid_tx ? 1 : 2;
  static const uint64_t expected_bob_balance = send_amount;
  static const uint64_t expected_alice_balance = 0;

  bool generate(std::vector<test_event_entry>& events) const;
};

class gen_double_spend_in_different_chains : public test_chain_unit_base {
public:
  static const uint64_t send_amount = MK_COINS(31);
  size_t expected_blockchain_height;

  gen_double_spend_in_different_chains();

  bool generate(std::vector<test_event_entry>& events) const;

  bool check_double_spend(CryptoNote::Core& c, size_t ev_index, const std::vector<test_event_entry>& events);
};

class TestGenerator;

#define INIT_DOUBLE_SPEND_TEST()                                                                                       \
  GENERATE_ACCOUNT(miner_account);                                                                                     \
  MAKE_GENESIS_BLOCK(events, blk_0, miner_account, ts_start);                                                          \
  MAKE_NEXT_BLOCK(events, blk_0f, blk_0, miner_account);                                                               \
  MAKE_ACCOUNT(events, bob_account);                                                                                   \
  MAKE_ACCOUNT(events, alice_account);                                                                                 \
  REWIND_BLOCKS(events, blk_0r, blk_0f, miner_account);                                                                \
  MAKE_TX(events, tx_0, miner_account, bob_account, send_amount, blk_0f);                                              \
  MAKE_NEXT_BLOCK_TX1(events, blk_1, blk_0r, miner_account, tx_0);                                                     \
  REWIND_BLOCKS(events, blk_1r, blk_1, miner_account);

#include "double_spend.inl"
