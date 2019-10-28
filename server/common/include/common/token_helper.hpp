#ifndef COMMON_TOKEN_HELPER_HPP
#define COMMON_TOKEN_HELPER_HPP

#include <cassert>
#include <chrono>
#include <gflags/gflags.h>
#include <iostream>
#include <jwt/jwt.hpp>
#include <memory>

DECLARE_string(db);

namespace Common {
namespace TokenHelper {

const uint64_t kExpirationDelaySeconds = 3600;
const jwt::string_view kUsername = "username";
const jwt::string_view kPassword = "password";
const jwt::string_view kExpiration = "expiration";
const std::string kAlgorithm = "hs256";
const std::string kAuthorization = "Authorization";
const std::string kSecret = "inf3995";

// Inspired by https://github.com/arun11299/cpp-jwt
inline auto encode(const std::string& username, const std::string& password) {
  jwt::jwt_object token{jwt::params::algorithm(kAlgorithm), jwt::params::secret(kSecret),
                        jwt::params::payload({{"role", "student"}})};
  token.add_claim(std::string(username), username)
      .add_claim(std::string(password), password)
      .add_claim("exp", std::chrono::system_clock::now() + std::chrono::seconds{kExpirationDelaySeconds});
  return token;
}

inline auto decode(const std::unique_ptr<std::string>& token) {
  std::error_code errCode;

  try {
    auto decodedObj = jwt::decode(*token, jwt::params::algorithms({kAlgorithm}), errCode, jwt::params::secret(kSecret));

    std::string username = decodedObj.payload().get_claim_value<std::string>(kUsername);
    std::string password = decodedObj.payload().get_claim_value<std::string>(kPassword);

    Common::Database db = Common::Database(FLAGS_db);
    auto user = db.getUser(username);

    if (errCode.value() == static_cast<int>(jwt::VerificationErrc::TokenExpired) && user) {
        jwt::jwt_object refreshToken = encode(user->username, user->password);
        *token = std::string(refreshToken.signature());
    }
  } catch (const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
  return !bool(errCode);
}

}  // namespace TokenHelper
}  // namespace Common

#endif  // COMMON_TOKEN_HELPER_HPP