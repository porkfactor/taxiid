#include <cpprest/http_msg.h>
#include <cpprest/json.h>
#include <taxii/taxii.hpp>
#include "json.hpp"

namespace taxii
{
    namespace taxii2
    {
        class keys
        {
        public:
            static constexpr char const *api_roots = "api_roots";
            static constexpr char const *can_read = "can_read";
            static constexpr char const *can_write = "can_write";
            static constexpr char const *collections = "collections";
            static constexpr char const *contact = "contact";
            static constexpr char const *date_added = "date_added";
            static constexpr char const *dflt = "default";
            static constexpr char const *description = "description";
            static constexpr char const *failures = "failures";
            static constexpr char const *failure_count = "failure_count";
            static constexpr char const *id = "id";
            static constexpr char const *max_content_length = "max_content_length";
            static constexpr char const *media_types = "media_types";
            static constexpr char const *message = "message";
            static constexpr char const *objects = "objects";
            static constexpr char const *pendings = "pendings";
            static constexpr char const *pending_count = "pending_count";
            static constexpr char const *request_timestamp = "request_timestamp";
            static constexpr char const *status = "status";
            static constexpr char const *successes = "successes";
            static constexpr char const *success_count = "success_count";
            static constexpr char const *title = "title";
            static constexpr char const *total_count = "total_count";
            static constexpr char const *versions = "versions";
        };

        class status
        {
        public:
            static constexpr char const *complete = "complete";
            static constexpr char const *pending = "pending";
        };
    };
}

namespace taxii
{
    void taxii2_discovery(
            web::http::http_request &request,
            web::http::http_response &response,
            taxii::service &service)
    {
        web::json::value o = web::json::value::object();
        web::json::value a = web::json::value::array();

        o[taxii::taxii2::keys::title] = web::json::value(service.title());
        o[taxii::taxii2::keys::description] = web::json::value(service.description());
        o[taxii::taxii2::keys::contact] = web::json::value(service.contact());
        o[taxii::taxii2::keys::dflt] = web::json::value(""); /* TODO: default API */

        for(auto const &i : service.apis())
        {
            a[a.size()] = web::json::value::string(i->uri());
        }

        o[taxii::taxii2::keys::api_roots] = a;

        response.set_body(o);
    }

    void taxii2_api_root(
            web::http::http_request &request,
            web::http::http_response &response,
            taxii::api &api)
    {
        web::json::value o = web::json::value::object();

        o[taxii::taxii2::keys::title] = web::json::value(api.title());
        o[taxii::taxii2::keys::description] = web::json::value(api.description());
        o[taxii::taxii2::keys::versions] = web::json::value::array();
        o[taxii::taxii2::keys::max_content_length] = web::json::value::number(0);

        response.set_body(o);
    }

    /*
    * GET http://example.org/<api>/status/<id>/
    */
    void taxii2_api_status(
            web::http::http_request &request,
            web::http::http_response &response,
            taxii::api &api)
    {
        web::json::value o = web::json::value::object();

        o[taxii::taxii2::keys::id] = web::json::value::string("");
        o[taxii::taxii2::keys::status] = web::json::value::string(taxii::taxii2::status::pending);
        o[taxii::taxii2::keys::request_timestamp] = web::json::value::string("");
        o[taxii::taxii2::keys::total_count] = web::json::value::number(0);
        o[taxii::taxii2::keys::success_count] = web::json::value::number(0);
        o[taxii::taxii2::keys::successes] = web::json::value::array();
        o[taxii::taxii2::keys::failure_count] = web::json::value::number(0);
        o[taxii::taxii2::keys::failures] = web::json::value::array();
        o[taxii::taxii2::keys::pending_count] = web::json::value::number(0);
        o[taxii::taxii2::keys::pendings] = web::json::value::array();

        response.set_body(o);
    }

    /*
    * GET http://example.org/<api>/collections
    */
    void taxii2_api_collections(
            web::http::http_request &request,
            web::http::http_response &response,
            taxii::api &api)
    {
        web::json::value o = web::json::value::object();
        web::json::value a = web::json::value::array();

        for(auto const &collection : api.collections())
        {
            web::json::value c = web::json::value::object();
            
            c[taxii::taxii2::keys::id] = web::json::value::string(collection->id());
            c[taxii::taxii2::keys::title] = web::json::value::string(collection->title());
            c[taxii::taxii2::keys::description] = web::json::value::string(collection->description());
            c[taxii::taxii2::keys::can_read] = web::json::value::boolean(collection->can_read());
            c[taxii::taxii2::keys::can_write] = web::json::value::boolean(collection->can_write());

            a[a.size()] = c;
        }

        o[taxii::taxii2::keys::collections] = a;

        response.set_body(o);
    }
}


/*
 * GET http://example.org/<api>/collections/<id>/manifest
 */
void taxii2_manifest(web::http::http_request &request, taxii::api &api)
{
    web::json::value o = web::json::value::object();
    web::json::value a = web::json::value::array();

    taxii::collection collection("", "", "");

    for(auto const &stix_object : collection.objects())
    {
        web::json::value stix = web::json::value::object();

        stix[taxii::taxii2::keys::id] = web::json::value::string("");

    }

    o[taxii::taxii2::keys::objects] = a;

    std::stringstream ss;
#if 0
    rapidjson::Writer<rapidjson::OStreamWrapper> w(rapidjson::OStreamWrapper(ss));

    /* locate the collection */

    w.StartObject();
    w.Key(taxii::taxii2::keys::objects);
    w.StartArray();

#if 0
    for(auto const &stix_object : collection.objects())
    {
        w.StartObject();
        w.Key(taxii::taxii2::keys::id);
        w.String("");
        w.Key(taxii::taxii2::keys::date_added);
        w.String("");
        w.Key(taxii::taxii2::keys::versions);
        w.StartArray();
        w.EndArray();
        w.Key(taxii::taxii2::keys::media_types);
        w.StartArray();
        w.EndArray();
        w.EndObject();
    }
#endif

    w.EndArray();

    w.EndObject();
#endif

    request.reply(web::http::status_codes::OK, ss.str());
}
