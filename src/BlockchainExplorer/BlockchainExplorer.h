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

#include <mutex>
#include <atomic>
#include <unordered_set>

#include "IBlockchainExplorer.h"
#include "IDataBase.h"
#include "INode.h"

#include "BlockchainExplorerErrors.h"
#include "Common/ObserverManager.h"
#include "Serialization/BinaryInputStreamSerializer.h"
#include "Serialization/BinaryOutputStreamSerializer.h"
#include "Wallet/WalletAsyncContextCounter.h"

#include "Logging/LoggerRef.h"

namespace CryptoNote {

enum State {
  NOT_INITIALIZED,
  INITIALIZED
};

class BlockchainExplorer : public IBlockchainExplorer, public INodeObserver {
public:
  BlockchainExplorer(INode& node, Logging::ILogger& logger/*, IDataBase& dataBase*/);

  BlockchainExplorer(const BlockchainExplorer&) = delete;
  BlockchainExplorer(BlockchainExplorer&&) = delete;

  BlockchainExplorer& operator=(const BlockchainExplorer&) = delete;
  BlockchainExplorer& operator=(BlockchainExplorer&&) = delete;

  virtual ~BlockchainExplorer();
    
  virtual bool addObserver(IBlockchainObserver* observer) override;
  virtual bool removeObserver(IBlockchainObserver* observer) override;

  virtual bool getBlocks(const std::vector<uint32_t>& blockHeights, std::vector<std::vector<BlockDetails>>& blocks) override;
  virtual bool getBlocks(const std::vector<Crypto::Hash>& blockHashes, std::vector<BlockDetails>& blocks) override;
  virtual bool getBlocks(uint64_t timestampBegin, uint64_t timestampEnd, uint32_t blocksNumberLimit, std::vector<BlockDetails>& blocks, uint32_t& blocksNumberWithinTimestamps) override;

  virtual bool getBlockchainTop(BlockDetails& topBlock) override;

  virtual bool getTransactions(const std::vector<Crypto::Hash>& transactionHashes, std::vector<TransactionDetails>& transactions) override;
  virtual bool getTransactionsByPaymentId(const Crypto::Hash& paymentId, std::vector<TransactionDetails>& transactions) override;
  virtual bool getPoolState(const std::vector<Crypto::Hash>& knownPoolTransactionHashes, Crypto::Hash knownBlockchainTop, bool& isBlockchainActual, std::vector<TransactionDetails>& newTransactions, std::vector<Crypto::Hash>& removedTransactions) override;

  virtual uint64_t getRewardBlocksWindow() override;
  virtual uint64_t getFullRewardMaxBlockSize(uint8_t majorVersion) override;

  virtual bool isSynchronized() override;

  virtual void init() override;
  virtual void shutdown() override;

  virtual void poolChanged() override;
  virtual void blockchainSynchronized(uint32_t topIndex) override;
  virtual void localBlockchainUpdated(uint32_t index) override;
  virtual void chainSwitched(uint32_t newTopIndex, uint32_t commonRoot, const std::vector<Crypto::Hash>& hashes) override;

  typedef WalletAsyncContextCounter AsyncContextCounter;

private:
  void poolUpdateEndHandler();

  class PoolUpdateGuard {
  public:
    PoolUpdateGuard();

    bool beginUpdate();
    bool endUpdate();

  private:
    enum class State {
      NONE,
      UPDATING,
      UPDATE_REQUIRED
    };

    std::atomic<State> m_state;
  };

  bool getBlockchainTop(BlockDetails& topBlock, bool checkInitialization);
  bool getBlocks(const std::vector<uint32_t>& blockHeights, std::vector<std::vector<BlockDetails>>& blocks, bool checkInitialization);

  void rebuildIndexes();
  void handleBlockchainUpdatedNotification(const std::vector<std::vector<BlockDetails>>& blocks);

  BlockDetails knownBlockchainTop;
  std::unordered_map<Crypto::Hash, TransactionDetails> knownPoolState;

  std::atomic<State> state;
  std::atomic<bool> synchronized;
  std::atomic<uint32_t> observersCounter;
  Tools::ObserverManager<IBlockchainObserver> observerManager;

  std::mutex mutex;

  INode& node;
  Logging::LoggerRef logger;
  IDataBase& database;

  AsyncContextCounter asyncContextCounter;
  PoolUpdateGuard poolUpdateGuard;
};
}
