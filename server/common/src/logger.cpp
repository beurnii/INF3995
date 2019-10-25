#include "common/logger.hpp"
#include <common/database.hpp>
#include <common/format_helper.hpp>

namespace Common {

bool Logger::isInitialized_ = false;
std::shared_ptr<Logger> Logger::instance_;
std::vector<std::string> Logger::severities_ = {"ERREUR", "ATTENTION", "INFO"};

Logger::Logger(int logSessionId, std::string dbPath) : logSessionId_(logSessionId), dbPath_(dbPath) { logCount_ = 1; }

std::shared_ptr<Logger> Logger::get() { return instance_; }

void Logger::init(const std::string& dbPath) {
  if (!isInitialized_) {
    Common::Database db(dbPath);
    auto logSessionId = db.addLogSession();
    instance_ = std::make_shared<Logger>(logSessionId, dbPath);
    isInitialized_ = true;
  }
}

void Logger::log(int severity, int provenance, const std::string& log) {
  std::lock_guard<std::mutex> lock(mutex_);
  Common::Database db(dbPath_);
  auto nowStr = Common::FormatHelper::nowStr();
  std::cout << logCount_ << ": " << severities_[severity] << ": " << nowStr << ": " << provenance << ": " << log
            << std::endl;
  db.addLog(logCount_, severity, provenance, nowStr, log, logSessionId_);
  ++logCount_;
}

}  // namespace Common
