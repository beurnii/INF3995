#include <algorithm>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <miner/block.hpp>
#include <nlohmann/json.hpp>
#include <picosha2.h>
#include <sstream>

namespace Miner {

Block::Block() {
  id_ = 0;
  dirty_ = true;
  nonce_ = 0;
}

Block::Block(unsigned int id, const std::string& previous) : Block() {
  id_ = id;
  previousHash_ = previous;
}

std::optional<Block> Block::fromBlockFile(const std::filesystem::path& blockDir) {
  std::ifstream blockFile(blockDir, std::ifstream::in);
  if (blockFile.fail()) {
    std::cerr << "couldn't open `" << blockDir.string() << "`" << std::endl;
    return {};
  }

  nlohmann::json json;
  blockFile >> json;
  blockFile.close();

  return json.get<Block>();
}

void Block::append(const std::string& data) {
  dirty_ = true;
  data_.push_back(data);
}

void Block::mine(unsigned int difficulty) {
  nonce_ = 0;

  bool invalid = true;
  while (invalid) {
    std::string blockHash = hash();
    invalid = false;
    for (unsigned int i = 0; i < difficulty; i++) {
      if (blockHash[i] != '0') {
        nonce_++;
        dirty_ = true;
        invalid = true;
      }
    }
  }
}

void Block::save(const std::filesystem::path& blockDir) const {
  std::filesystem::path path(blockDir / std::to_string(id_));
  std::ofstream file(path, std::ofstream::out);
  std::string json = static_cast<nlohmann::json>(*this).dump();
  file << json;
  file.close();
}

unsigned int Block::id() const { return id_; }

unsigned int Block::nonce() const { return nonce_; }

std::string Block::hash() {
  if (!dirty_) {
    return hash_;
  }

  std::string json = static_cast<nlohmann::json>(*this).dump();
  std::vector<unsigned char> hash(picosha2::k_digest_size);
  picosha2::hash256(json.begin(), json.end(), hash.begin(), hash.end());
  hash_ = picosha2::bytes_to_hex_string(hash.begin(), hash.end());
  dirty_ = false;

  return hash_;
}

std::string Block::previousHash() const { return previousHash_; }

const std::vector<std::string>& Block::data() const { return data_; }

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const Block& obj) {
  j = {
      {obj.kId_, obj.id()},
      {obj.kNonce_, obj.nonce()},
      {obj.kPreviousHash_, obj.previousHash()},
      {obj.kData_, obj.data()},
  };
}

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, Block& obj) {
  obj.dirty_ = true;
  j.at(obj.kId_).get_to(obj.id_);
  j.at(obj.kNonce_).get_to(obj.nonce_);
  j.at(obj.kPreviousHash_).get_to(obj.previousHash_);
  j.at(obj.kData_).get_to(obj.data_);
}

}  // namespace Miner