#include <taxii/taxii.hpp>
#include <cpprest/http_listener.h>
#include "../log.hpp"

namespace taxii
{
    class basic_taxii_listener
    {
    public:
        basic_taxii_listener(web::http::uri const &uri) : listener_(uri)
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

        void get(web::http::http_request request)
        {
            web::http::http_response response(web::http::status_codes::MethodNotAllowed);

            spdlog::info("GET {}", request.request_uri().to_string());

            if(check_headers(request.headers()))
            {

            }
            else
            {

            }

            request.reply(response);


            /*
            * 2/ check authentication method(s)
            * 3/ check uri, handover to handler
            * 4/ check
            * 
            */
        }

        void post(web::http::http_request request)
        {
            spdlog::info("POST {}", request.request_uri().to_string());

            if(check_headers(request.headers()))
            {
                request.reply(web::http::status_codes::OK);
            }
            else
            {
                request.reply(web::http::status_codes::NotFound);
            }
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
        basic_discovery_service(web::http::uri const &uri, std::shared_ptr<taxii::service> s) :
            basic_taxii_service(uri),
            service_(s)
        {

        }

    private:
        std::shared_ptr<taxii::service> service_;
    };

    class basic_api_service : public basic_taxii_service
    {
    public:
        basic_api_service(web::http::uri const &uri, std::shared_ptr<taxii::api> a) :
            basic_taxii_service(uri),
            api_(a)
        {

        }

    private:
        std::shared_ptr<taxii::api> api_;
    };

    class basic_status_service : public basic_taxii_service
    {
    public:
        basic_status_service(web::http::uri const &uri, std::shared_ptr<taxii::api> a) :
            basic_taxii_service(uri),
            api_(a)
        {

        }

    private:
        std::shared_ptr<taxii::api> api_;
    };

    class basic_collection_service : public basic_taxii_service
    {
    public:
        basic_collection_service(web::http::uri const &uri, std::shared_ptr<taxii::api> a) :
            basic_taxii_service(uri),
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
                new basic_api_service(listener_->root_.to_string() + api->title(), api);
                new basic_status_service(listener_->root_.to_string() + api->title() + "/status", api);
                new basic_collection_service(listener_->root_.to_string() + api->title() + "/collections", api);
            } 

        private:
            taxii::listener::impl *listener_;
        };

        web::http::uri root_;
        std::shared_ptr<taxii::service> service_;
        std::unique_ptr<basic_discovery_service> discovery_;
        service_listener service_listener_;
    };

#if 0
    class listener
    {
    public:
        listener(std::string const &uri, std::shared_ptr<service> s) :
            root_(uri),
            service_(s),
            service_listener_(this)
        {
            discovery_.reset(new basic_discovery_service(root_.to_string() + "taxii", s));

            s->addListener(&service_listener_);
        }

        web::http::uri const &root() const { root_; }

    private:
    };
#endif

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