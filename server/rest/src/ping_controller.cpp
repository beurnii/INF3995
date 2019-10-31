#include <rest/ping_controller.hpp>

namespace Rest {

PingController::PingController(const std::shared_ptr<Rest::CustomRouter>& router) {
  setupRoutes(router);
}

void PingController::setupRoutes(const std::shared_ptr<Rest::CustomRouter>& router) {
  router->get("/ping", Pistache::Rest::Routes::bind(&PingController::handlePing, this), false);
  router->get("/sping", Pistache::Rest::Routes::bind(&PingController::handlePing, this));
}

void PingController::handlePing(const Pistache::Rest::Request& /*unused*/, Pistache::Http::ResponseWriter response) {
  response.send(Pistache::Http::Code::Ok, "PONG");
}

}  // namespace Rest
