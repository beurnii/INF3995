#ifndef REST_CUSTOM_ROUTER_HPP
#define REST_CUSTOM_ROUTER_HPP

#include <pistache/endpoint.h>
#include <pistache/http.h>
#include <pistache/router.h>

namespace Rest {

class CustomRouter : public Pistache::Rest::Router {
 public:
  CustomRouter();

  void addRoute(Pistache::Http::Method method, const std::string& url,
                Pistache::Rest::Route::Handler handler);

  void get(const std::string& url, Pistache::Rest::Route::Handler handler);
  void post(const std::string& url, Pistache::Rest::Route::Handler handler);

 private:
  static void log(const std::string& url, const Pistache::Rest::Request& request, int logSessionId);
  
  int logSessionId_;
};

}  // namespace Rest

#endif  // REST_CUSTOM_ROUTER_HPP
