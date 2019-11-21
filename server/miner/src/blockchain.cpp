#include "miner/blockchain.hpp"

#include "common/gflags_helper.hpp"
#include "common/logger.hpp"
#include <exception>
#include <fstream>
#include <iostream>

DECLARE_int32(difficulty);

namespace Miner {

const std::string BlockChain::kMetadataFilename = "metadata";

BlockChain::BlockChain() {
  difficulty_ = FLAGS_difficulty;
  std::cout << "Starting blockchain with difficulty " << difficulty_ << std::endl;
  createBlock();
  saveAll();
  std::cout << "Saved genesys block" << std::endl;
}

BlockChain::BlockChain(const std::filesystem::path& blockDir) : BlockChain() { blockDir_ = blockDir; }

std::optional<BlockChain> BlockChain::fromDirectory(const std::filesystem::path& blockDir) {
  std::filesystem::create_directories(blockDir);
  if (blockDir.empty()) {
    return BlockChain(blockDir);
  }

  if (!std::filesystem::exists(blockDir / BlockChain::kMetadataFilename)) {
    return BlockChain(blockDir);
  }

  std::optional<BlockChain> blockchain = loadMetadataBlockChain(blockDir);
  if (!blockchain) {
    return {};
  }

  unsigned int lastBlockID = blockchain->lastBlockID();
  blockchain->clearAll();
  if (!blockchain->getBlock(lastBlockID)) {
    return {};
  }

  return blockchain;
}

void BlockChain::appendTransaction(const std::string& transaction) { lastBlock()->get().append(transaction); }

void BlockChain::saveAll() {
  Common::optional_ref<Block> last = lastBlock();
  if (last) {
    lastBlock()->get().save();
  }
  saveMetadata();
}

void BlockChain::clearAll() { blocks_.clear(); }

Block& BlockChain::nextBlock() {
  lastBlock()->get().mine(difficulty_);
  lastBlock()->get().save();

  return createBlock();
}

Common::optional_ref<Block> BlockChain::lastBlock() {
  if (blocks_.empty()) {
    return {};
  }

  return blocks_.rbegin()->second;
}

Common::optional_ref<Block> BlockChain::getBlock(unsigned int id) {
  auto it = blocks_.find(id);
  if (it == blocks_.end()) {
    return loadBlock(id);
  }

  return it->second;
}

unsigned int BlockChain::lastBlockID() const { return blocks_.rbegin()->first; }

const std::map<unsigned int, Block>& BlockChain::blocks() { return blocks_; }

unsigned int BlockChain::difficulty() const { return difficulty_; }

Block& BlockChain::createBlock() {
  unsigned int nextID = 0;
  std::string previousHash;

  Common::optional_ref<Block> last = lastBlock();
  if (last) {
    nextID = last->get().id() + 1;
    previousHash = last->get().hash();
  }

  blocks_.emplace(std::piecewise_construct, std::forward_as_tuple(nextID), std::forward_as_tuple(nextID, previousHash));
  return blocks_.at(nextID);
}

Common::optional_ref<Block> BlockChain::loadBlock(unsigned int id) {
  std::filesystem::path blockPath(blockDir_ / std::to_string(id));

  std::optional<Block> block = Block::fromBlockFile(blockPath);
  if (!block) {
    Common::Logger::get()->error("Block #" + std::to_string(id) + " doesn't exist\n");
    return {};
  }

  if (block->id() != id) {
    Common::Logger::get()->error("Mismatch ID in block #" + std::to_string(id) + "\n");
    return {};
  }

  blocks_.erase(block->id());
  blocks_.emplace(block->id(), block.value());
  return block.value();
}

bool BlockChain::saveMetadata() const {
  std::ofstream metadataFile(blockDir_ / BlockChain::kMetadataFilename, std::ofstream::out);
  if (metadataFile.fail()) {
    Common::Logger::get()->error("Blockchain: failed to open metadata in `" + std::string(blockDir_) + "`\n");
    return false;
  }

  std::string json = static_cast<nlohmann::json>(*this).dump();
  metadataFile << json;
  metadataFile.close();

  return true;
}

std::optional<BlockChain> BlockChain::loadMetadataBlockChain(const std::filesystem::path& blockDir) {
  std::ifstream metadataFile(blockDir / BlockChain::kMetadataFilename, std::ifstream::in);
  if (metadataFile.fail()) {
    Common::Logger::get()->error("Blockchain: failed to open metadata in `" + std::string(blockDir) + "`\n");
    return {};
  }

  nlohmann::json json;
  metadataFile >> json;
  metadataFile.close();

  std::optional<BlockChain> metadata = json.get<BlockChain>();
  metadata->blockDir_ = blockDir;

  return metadata;
}

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const BlockChain& obj) {
  j = {
      {obj.kLastBlock_, obj.lastBlockID()},
      {obj.kDifficulty_, obj.difficulty()},
  };
}

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, BlockChain& obj) {
  unsigned int lastBlock;
  j.at(obj.kLastBlock_).get_to(lastBlock);
  j.at(obj.kDifficulty_).get_to(obj.difficulty_);
  obj.blocks_.insert(std::pair<unsigned int, Block>(lastBlock, Block()));
}

}  // namespace Miner
