#include <iostream>
#include <cpprest/http_listener.h>
#include "log.hpp"

class basic_taxii_listener
{
public:
    basic_taxii_listener(web::http::uri const &uri) : listener_(uri)
    {
        listener_.support(web::http::methods::GET, std::bind(&basic_taxii_listener::get, this, std::placeholders::_1));
        listener_.support(web::http::methods::PUT, std::bind(&basic_taxii_listener::put, this, std::placeholders::_1));
    }

    virtual ~basic_taxii_listener()
    {

    }

    void get(web::http::http_request request)
    {
        if(check_headers(request.headers()))
        {

        }
        else
        {
            request.reply(web::http::status_codes::NotFound);
        }


        /*
         * 2/ check authentication method(s)
         * 3/ check uri, handover to handler
         * 4/ check
         * 
         */
    }

    void put(web::http::http_request request)
    {

    }

protected:
    bool check_headers(web::http::http_headers const &headers)
    {
        for(auto const &header : headers)
        {
            if(header.first == web::http::header_names::accept)
            {

            }
            else if(header.first == web::http::header_names::accept_ranges)
            {

            }
            else if(header.first == web::http::header_names::authorization)
            {

            }
            else if(header.first == web::http::header_names::content_range)
            {

            }
            else if(header.first == web::http::header_names::content_type)
            {

            }
            else if(header.first == web::http::header_names::range)
            {

            }
            else if(header.first == web::http::header_names::www_authenticate)
            {

            }
        }

        return true;
    }

private:
    web::http::experimental::listener::http_listener listener_;
};

class basic_taxii_service
{
public:
    basic_taxii_service(web::http::uri const &uri) :
        listener_(uri)
    {

    }

protected:

private:
    basic_taxii_listener listener_;
};

class basic_discovery_service : public basic_taxii_service
{
public:
    basic_discovery_service(web::http::uri const &uri) :
        basic_taxii_service(uri)
    {

    }

private:

};

class basic_poll_service : public basic_taxii_service
{
public:
    basic_poll_service(web::http::uri const &uri) :
        basic_taxii_service(uri)
    {

    }

private:

};

class basic_inbox_service : public basic_taxii_service
{
public:
    basic_inbox_service(web::http::uri const &uri) :
        basic_taxii_service(uri)
    {

    }

private:

};

class collection
{
public:

private:

};

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
    void handleGet(web::http::http_request message) override {
        std::cout << "request.uri = [" 
            << "absolute: " << message.absolute_uri().to_string()
            << ","
            << "relative: " << message.relative_uri().to_string()
            << "]"
            << std::endl;

        message.reply(web::http::status_codes::OK);
    }
    void handlePut(web::http::http_request message) override { }
    void handlePost(web::http::http_request message) override { }
    void handlePatch(web::http::http_request message) override { }
    void handleDelete(web::http::http_request message) override { }
    void handleHead(web::http::http_request message) override { }
    void handleOptions(web::http::http_request message) override { }
    void handleTrace(web::http::http_request message) override { }
    void handleConnect(web::http::http_request message) override { }
    void handleMerge(web::http::http_request message) override { }
    void initRestOpHandlers() override
    {
        _listener.support(web::http::methods::GET, std::bind(&MicroserviceController::handleGet, this, std::placeholders::_1));
        _listener.support(web::http::methods::PUT, std::bind(&MicroserviceController::handlePut, this, std::placeholders::_1));
        _listener.support(web::http::methods::POST, std::bind(&MicroserviceController::handlePost, this, std::placeholders::_1));
        _listener.support(web::http::methods::DEL, std::bind(&MicroserviceController::handleDelete, this, std::placeholders::_1));
        _listener.support(web::http::methods::PATCH, std::bind(&MicroserviceController::handlePatch, this, std::placeholders::_1));
    }

private:
    static web::json::value responseNotImpl(const web::http::method & method);
};

int main(int argc, const char * argv[]) {
    MicroserviceController s1, s2;
    s1.setEndpoint("http://host_auto_ip4:6502/abc");
    s2.setEndpoint("http://host_auto_ip4:6502/xyz");
    
    auto logger = spdlog::stdout_color_mt("console");

    spdlog::set_default_logger(logger);

    try {
        // wait for server initialization...
        s1.accept().wait();
        s2.accept().wait();
        spdlog::info("Modern C++ Microservice now listening for requests at: {}", s1.endpoint());
        spdlog::info("Modern C++ Microservice now listening for requests at: {}", s2.endpoint());
   
        while(1)
        {
            sleep(100);
        }

        s1.shutdown().wait();
        s2.shutdown().wait();
    }
    catch(std::exception & e) {
        spdlog::error("exception: {}", e.what());
    }
    catch(...) {
        // RuntimeUtils::printStackTrace();
    }

    return 0;
}