#include <taxii/taxii.hpp>
#include <cpprest/http_listener.h>
#include "../log.hpp"

namespace taxii
{
    class basic_taxii_listener
    {
    public:
        basic_taxii_listener(web::http::uri const &uri) :
            listener_(uri)
        {
            spdlog::info("creating endpoint {}", uri.to_string());

            listener_.support(web::http::methods::GET, std::bind(&basic_taxii_listener::get, this, std::placeholders::_1));
            listener_.support(web::http::methods::POST, std::bind(&basic_taxii_listener::post, this, std::placeholders::_1));

            listener_.open();
        }

        virtual ~basic_taxii_listener()
        {
            listener_.close();
        }

        virtual void perform_get(web::http::http_request &request, web::http::http_response &response)
        {
            response.set_status_code(web::http::status_codes::MethodNotAllowed);
        }

        virtual void perform_post(web::http::http_request &request, web::http::http_response &response)
        {
            response.set_status_code(web::http::status_codes::MethodNotAllowed);
        }

    protected:
        bool check_headers(web::http::http_request const &request, web::http::http_response &response)
        {
            for(auto const &header : request.headers())
            {
                if(header.first == web::http::header_names::accept)
                {
                    /* TODO: this isn't the way to do it! */
                    response.headers().set_content_type(header.second);
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
        void get(web::http::http_request request)
        {
            web::http::http_response response(web::http::status_codes::OK);

            spdlog::info("GET {}", request.request_uri().to_string());

            if(check_headers(request, response))
            {
                perform_get(request, response);
            }
            else
            {

            }

            request.reply(response);
        }

        void post(web::http::http_request request)
        {
            web::http::http_response response(web::http::status_codes::MethodNotAllowed);

            spdlog::info("POST {}", request.request_uri().to_string());

            if(check_headers(request, response))
            {
                perform_post(request, response);
            }
            else
            {

            }

            request.reply(response);
        }

        web::http::experimental::listener::http_listener listener_;
    };

    extern void taxii2_discovery(web::http::http_request &request,
        web::http::http_response &response,
        taxii::service &service);


    class basic_discovery_service : public basic_taxii_listener
    {
    public:
        basic_discovery_service(web::http::uri const &uri, std::shared_ptr<taxii::service> s) :
            basic_taxii_listener(uri),
            service_(s)
        {

        }

        virtual void perform_get(web::http::http_request &request, web::http::http_response &response) override
        {
            taxii2_discovery(request, response, *service_);
        }

    private:
        std::shared_ptr<taxii::service> service_;
    };

    class basic_api_service : public basic_taxii_listener
    {
    public:
        basic_api_service(web::http::uri const &uri, std::shared_ptr<taxii::api> a) :
            basic_taxii_listener(uri),
            api_(a)
        {

        }

    private:
        std::shared_ptr<taxii::api> api_;
    };

    class basic_status_service : public basic_taxii_listener
    {
    public:
        basic_status_service(web::http::uri const &uri, std::shared_ptr<taxii::api> a) :
            basic_taxii_listener(uri),
            api_(a)
        {

        }

    private:
        std::shared_ptr<taxii::api> api_;
    };

    class basic_collection_service : public basic_taxii_listener
    {
    public:
        basic_collection_service(web::http::uri const &uri, std::shared_ptr<taxii::api> a) :
            basic_taxii_listener(uri),
            api_(a)
        {

        }

    private:
        std::shared_ptr<taxii::api> api_;
    };

    struct listener::impl
    {
        impl(listener::string_type const &uri, std::shared_ptr<service> s) :
            root_(uri),
            service_(s),
            service_listener_(this)
        {
            discovery_.reset(new basic_discovery_service(root_.to_string() + "taxii", s));

            s->addListener(&service_listener_);
        }

        struct service_listener : public taxii::service::service_listener
        {
        public:
            service_listener(taxii::listener::impl *l) : listener_(l) { }

            virtual void onCreateApi(std::shared_ptr<taxii::api> api) override
            {
                api->uri(listener_->root_.to_string() + api->title());

                new basic_api_service(api->uri(), api);
                new basic_status_service(api->uri() + "/status", api);
                new basic_collection_service(api->uri() + "/collections", api);
            } 

        private:
            taxii::listener::impl *listener_;
        };

        web::http::uri root_;
        std::shared_ptr<taxii::service> service_;
        std::unique_ptr<basic_discovery_service> discovery_;
        service_listener service_listener_;
    };

    listener::listener(std::string const &uri, std::shared_ptr<taxii::service> s) :
        pimpl_(new impl(uri, s))
    {

    }

    listener::~listener()
    {
        delete pimpl_;
    }

    listener::string_type const &listener::root() const
    {
        return pimpl_->root_.to_string();
    }
}