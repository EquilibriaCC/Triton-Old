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

#include "CryptoNoteCore/Currency.h"
#include "INode.h"
#include "IWalletLegacy.h"
#include "System/Dispatcher.h"
#include "System/Event.h"
#include "WalletLegacy/WalletLegacy.h"

namespace Tests {
namespace Common {

class TestWalletLegacy : private CryptoNote::IWalletLegacyObserver {
public:
  TestWalletLegacy(System::Dispatcher& dispatcher, const CryptoNote::Currency& currency, CryptoNote::INode& node);
  ~TestWalletLegacy();

  std::error_code init();
  std::error_code sendTransaction(const std::string& address, uint64_t amount, Crypto::Hash& txHash);
  void waitForSynchronizationToHeight(uint32_t height);
  CryptoNote::IWalletLegacy* wallet();
  CryptoNote::AccountPublicAddress address() const;

protected:
  virtual void synchronizationCompleted(std::error_code result) override;
  virtual void synchronizationProgressUpdated(uint32_t current, uint32_t total) override;

private:
  System::Dispatcher& m_dispatcher;
  System::Event m_synchronizationCompleted;
  System::Event m_someTransactionUpdated;

  CryptoNote::INode& m_node;
  const CryptoNote::Currency& m_currency;
  std::unique_ptr<CryptoNote::IWalletLegacy> m_wallet;
  std::unique_ptr<CryptoNote::IWalletLegacyObserver> m_walletObserver;
  uint32_t m_currentHeight;
  uint32_t m_synchronizedHeight;
  std::error_code m_lastSynchronizationResult;
};

}
}
