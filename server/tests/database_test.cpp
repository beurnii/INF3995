#include <common/database.hpp>
#include <common/models.hpp>
#include <gtest/gtest.h>

TEST(Sqlite3Tests, get_user) {
  Common::Database db("test-blockchain.db");
  Common::Models::LoginRequest expectedUser = {"Anne-Sophie Provencher", "LOL1234!"};
  std::string expectedHash = "da6a850377faa387cea7c58a6ebd5935d5502a95aa0993848f8ae4ab8efc68ad";

  db.addUser(expectedUser);

  // auto receivedUser = db.getUser(expectedUser.username);
  auto receivedUser = db.containsUser(expectedUser);

  ASSERT_TRUE(receivedUser);
  // ASSERT_TRUE(receivedUser.has_value());
  // ASSERT_EQ(expectedUser.username, receivedUser->username);
  // ASSERT_EQ(expectedHash, receivedUser->password);
}
