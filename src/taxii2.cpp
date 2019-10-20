#include <cpprest/http_msg.h>
#include <rapidjson/writer.h>

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

class taxii_collection
{
public:
    std::string id;
    std::string title;
    std::string description;
    bool can_read;
    bool can_write;
};

class taxii_api
{
public:
    std::string title;
    std::string description;
    std::string uri;
    uint64_t max_content_length;

    std::vector<taxii_collection> collections;
};

class taxii_service
{
public:
    std::string title;
    std::string description;
    std::string contact;
    std::string uri; /* default API */

    std::vector<taxii_api> api;
};

void taxii2_discovery(web::http::http_request &request, taxii_service &service)
{
    std::stringstream ss;
    rapidjson::Writer w(ss);

    w.StartObject();
    w.Key(taxii::taxii2::keys::title);
    w.String(service.title.c_str(), service.title.length(), false);
    w.Key(taxii::taxii2::keys::description);
    w.String(service.description.c_str(), service.description.length(), false);
    w.Key(taxii::taxii2::keys::contact);
    w.String(service.contact.c_str(), service.contact.length(), false);
    w.Key(taxii::taxii2::keys::dflt);
    w.String(service.uri.c_str(), service.uri.length(), false);

    w.Key(taxii::taxii2::keys::api_roots);
    w.StartArray();
    for(auto const &i : service.api)
    {
        w.String(i.uri.c_str(), i.uri.length());
    }
    w.EndArray();

    request.reply(web::http::status_codes::OK, ss.str());
}

void taxii2_api_root(web::http::http_request &request, taxii_api &api)
{
    std::stringstream ss;
    rapidjson::Writer w(ss);

    w.StartObject();
    w.Key(taxii::taxii2::keys::title);
    w.String(api.title.c_str(), api.title.length(), false);
    w.Key(taxii::taxii2::keys::description);
    w.String(api.description.c_str(), api.description.length(), false);
    w.Key(taxii::taxii2::keys::versions);
    w.StartArray();
    w.EndArray();
    w.Key(taxii::taxii2::keys::max_content_length);
    w.Uint64(api.max_content_length);
    w.EndObject();

    request.reply(web::http::status_codes::OK, ss.str());
}

/*
 * GET http://example.org/<api>/status/<id>/
 */
void taxii2_status(web::http::http_request &request, taxii_api &api)
{
    std::stringstream ss;
    rapidjson::Writer w(ss);

    /* id: required */
    w.Key(taxii::taxii2::keys::id);
    w.String(""); /* TODO: ID string */
    /* status: required */
    w.Key(taxii::taxii2::keys::status);
    w.String(taxii::taxii2::status::pending); /* TODO: status */
    /* request_timestamp: optional */
    w.Key(taxii::taxii2::keys::request_timestamp);
    w.String(""); /* TODO */

    /* total_count: required */
    w.Key(taxii::taxii2::keys::total_count);
    w.Uint64(0); /* TODO */

    /* success_count: required */
    w.Key(taxii::taxii2::keys::success_count);
    w.Uint64(0); /* TODO */

    /* successes: optional */
    w.Key(taxii::taxii2::keys::successes);
    w.StartArray();
    w.EndArray();

    /* failure_count: required */
    w.Key(taxii::taxii2::keys::failure_count);
    w.Uint64(0); /* TODO */

    /* failures: optional */
    w.Key(taxii::taxii2::keys::failures);
    w.StartArray();
    /*
        w.StartObject();
        w.Key(taxii::taxii2::keys::id);
        w.Key(taxii::taxii2::keys::message);
        w.EndObject();

     */
    w.EndArray();

    /* pending_count: required */
    w.Key(taxii::taxii2::keys::pending_count);
    w.Uint64(0); /* TODO */

    /* pendings: optional */
    w.Key(taxii::taxii2::keys::pendings);
    w.StartArray();
    w.EndArray();
    w.EndObject();
}

/*
 * GET http://example.org/<api>/collections
 */
void taxii2_collections(web::http::http_request &request, taxii_api &api)
{
    std::stringstream ss;
    rapidjson::Writer w(ss);

    w.StartObject();
    w.Key(taxii::taxii2::keys::collections);
    w.StartArray();

    for(auto const &collection : api.collections)
    {
        w.StartObject();
        w.Key(taxii::taxii2::keys::id);
        w.String(collection.id.c_str(), collection.id.length());
        w.Key(taxii::taxii2::keys::title);
        w.String(collection.title.c_str(), collection.title.length());
        w.Key(taxii::taxii2::keys::description);
        w.String(collection.description.c_str(), collection.description.length());
        w.Key(taxii::taxii2::keys::can_read);
        w.Bool(collection.can_read);
        w.Key(taxii::taxii2::keys::can_write);
        w.Bool(collection.can_write);
        w.EndObject();
    }

    w.EndArray();

    w.EndObject();
}

/*
 * GET http://example.org/<api>/collections/<id>/manifest
 */
void taxii2_manifest(web::http::http_request &request, taxii_api &api)
{
    std::stringstream ss;
    rapidjson::Writer w(ss);

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
}