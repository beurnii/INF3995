#include <common/database.hpp>
#include <common/models.hpp>
#include <gflags/gflags.h>
#include <rest/info_controller.hpp>

DECLARE_string(db);

namespace Rest {

InfoController::InfoController(const std::shared_ptr<Rest::CustomRouter>& router,
                               const std::shared_ptr<ZMQWorker>& zmqWorker)
    : zmqWorker_(zmqWorker) {
  setupRoutes(router);
}

void InfoController::setupRoutes(const std::shared_ptr<Rest::CustomRouter>& router) {
  router->post(kBasePath_ + "cours", Pistache::Rest::Routes::bind(&InfoController::handleClasses, this));
  router->post(kBasePath_ + "etudiant", Pistache::Rest::Routes::bind(&InfoController::handleStudents, this));
}

void InfoController::handleClasses(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
  Common::Models::ClassesRequest classesRequest = nlohmann::json::parse(request.body());
  Common::Models::CheckForExistingClassRequest checkForExistingClassRequest = {classesRequest.acronym,
                                                                               classesRequest.trimester};
  auto classId = zmqWorker_->getRequest(
      {Common::Functions::checkForExistingClass, Common::Models::toStr(checkForExistingClassRequest)});
  std::vector<Common::Models::Result> results;
  if (classId.found) {
    auto classResult = zmqWorker_->getRequest({Common::Functions::getClassResult, classId.data});
    std::vector<Common::Models::Result> classResults = nlohmann::json::parse(classResult.data);
    results = classResults;
  }
  response.send(Pistache::Http::Code::Ok, Common::Models::toStr(results));
}

void InfoController::handleStudents(const Pistache::Rest::Request& request, Pistache::Http::ResponseWriter response) {
  Common::Models::StudentRequest studentRequest = nlohmann::json::parse(request.body());
  std::optional<Common::Models::Result> result;
  auto studentRes =
      zmqWorker_->getRequest({Common::Functions::getStudentResult, Common::Models::toStr(studentRequest)});
  std::vector<Common::Models::StudentResult> studentResults = nlohmann::json::parse(studentRes.data);
  Common::Models::StudentResponse studentResponse = {studentResults};

  response.send(Pistache::Http::Code::Ok, Common::Models::toStr(studentResponse));
}

}  // namespace Rest
