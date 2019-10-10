#include <iostream>
#include <cpprest/http_listener.h>

namespace cfx {
    class BasicController {
    public:
        typedef web::http::experimental::listener::http_listener http_listener;

        BasicController() {

        }

        ~BasicController() {

        }

        void setEndpoint(const std::string & value) {
            web::http::uri endpointURI(value);
            web::http::uri_builder endpointBuilder;

            endpointBuilder.set_scheme(endpointURI.scheme());
            if (endpointURI.host() == "host_auto_ip4") {
                endpointBuilder.set_host("0.0.0.0");
            }
            else if (endpointURI.host() == "host_auto_ip6") {
                endpointBuilder.set_host("::");
            }
            endpointBuilder.set_port(endpointURI.port());
            endpointBuilder.set_path(endpointURI.path());

            _listener = http_listener(endpointBuilder.to_uri());
        }

        std::string endpoint() const {
            return _listener.uri().to_string();
        }

        pplx::task<void> accept() {
            initRestOpHandlers();
            return _listener.open();
        }

        pplx::task<void> shutdown() {
            return _listener.close();
        }

        std::vector<utility::string_t> requestPath(const web::http::http_request & message) {
            auto relativePath = web::http::uri::decode(message.relative_uri().path());
            return web::http::uri::split_path(relativePath);        
        }

        virtual void initRestOpHandlers() = 0;

    protected:
        http_listener _listener; // main micro service network endpoint
    };

    class Controller {
    public: 
        virtual void handleGet(web::http::http_request message) = 0;
        virtual void handlePut(web::http::http_request message) = 0;
        virtual void handlePost(web::http::http_request message) = 0;
        virtual void handleDelete(web::http::http_request message) = 0;
        virtual void handlePatch(web::http::http_request messge) = 0;
        virtual void handleHead(web::http::http_request message) = 0;
        virtual void handleOptions(web::http::http_request message) = 0;
        virtual void handleTrace(web::http::http_request message) = 0;
        virtual void handleConnect(web::http::http_request message) = 0;
        virtual void handleMerge(web::http::http_request message) = 0;
    };
}

class MicroserviceController : public cfx::BasicController, cfx::Controller {
public:
    MicroserviceController() : BasicController() {}
    ~MicroserviceController() {}
    void handleGet(web::http::http_request message) override { }
    void handlePut(web::http::http_request message) override { }
    void handlePost(web::http::http_request message) override { }
    void handlePatch(web::http::http_request message) override { }
    void handleDelete(web::http::http_request message) override { }
    void handleHead(web::http::http_request message) override { }
    void handleOptions(web::http::http_request message) override { }
    void handleTrace(web::http::http_request message) override { }
    void handleConnect(web::http::http_request message) override { }
    void handleMerge(web::http::http_request message) override { }
    void initRestOpHandlers() override { }

private:
    static web::json::value responseNotImpl(const web::http::method & method);
};

int main(int argc, const char * argv[]) {
    MicroserviceController server;
    server.setEndpoint("http://host_auto_ip4:6502/v1/ivmero/api");
    
    try {
        // wait for server initialization...
        server.accept().wait();
        std::cout << "Modern C++ Microservice now listening for requests at: " << server.endpoint() << '\n';
   
        while(1)
        {
            sleep(100);
        }

        server.shutdown().wait();
    }
    catch(std::exception & e) {
        std::cerr << e.what() << "\n";
    }
    catch(...) {
        // RuntimeUtils::printStackTrace();
    }

    return 0;
}