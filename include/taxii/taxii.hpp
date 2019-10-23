#ifndef TAXII_HPP_
#define TAXII_HPP_

#include <string>
#include <vector>
#include <memory>

class basic_object
{

};

namespace stix
{
    class object : public basic_object
    {

    };
};

namespace taxii
{
    static constexpr char const *TAXII_1_MEDIA_TYPE = "";
    static constexpr char const *TAXII_2_MEDIA_TYPE = "application/vnd.oasis.taxii+json";
    static constexpr char const *STIX_2_MEDIA_TYPE = "application/vnd.oasis.stix+json";

    static constexpr char const *TAXII_2_ENDPOINT = "/taxii";

    typedef std::string string_type;

    class basic_taxii_endpoint
    {

    };

    class basic_discovery_endpoint : public basic_taxii_endpoint
    {

    };

    class basic_status_endpoint : public basic_taxii_endpoint
    {

    };

    class collection
    {
    public:
        typedef std::vector<stix::object> object_container_type;
        typedef taxii::string_type string_type;

        collection(string_type const &i, string_type const &t, string_type const &d) :
            id_(i),
            title_(t),
            description_(d)
        {
            
        }

        string_type const &id() const { return id_; }
        string_type const &title() const { return title_; }
        string_type const &description() const { return description_; }

        bool can_read() const { return true; }
        bool can_write() const { return true; }

        object_container_type const &objects() const { return objects_; }

    private:
        object_container_type objects_;
        string_type id_;
        string_type title_;
        string_type description_;
    };

    class api
    {
    public:
        typedef std::vector<std::shared_ptr<collection>> collection_container_type;
        typedef taxii::string_type string_type;

        api(string_type const &t, string_type const &d) :
            title_(t),
            description_(d)
        {

        }

        string_type const &title() const { return title_; }
        string_type const &description() const { return description_; }
        string_type const &uri() const { return uri_; }

        void uri(string_type const &u) { uri_ = u; }

        collection_container_type const &collections() const { return collections_; }

        std::shared_ptr<collection> createCollection(string_type const &);

    private:
        collection_container_type collections_;
        string_type title_;
        string_type description_;
        string_type uri_;
    };

    class service
    {
    public:
        typedef std::vector<std::shared_ptr<api>> api_container_type;
        typedef taxii::string_type string_type;

        class service_listener
        {
        public:
            virtual ~service_listener() { }
            virtual void onCreateApi(std::shared_ptr<api>) { };
            virtual void onDestroyApi(std::shared_ptr<api>) { };
        };

        service(string_type const &t, string_type const &d);
        ~service();

        string_type const &title() const { return title_; }
        string_type const &description() const { return description_; }
        string_type const &contact() const { return contact_; }

        api_container_type const &apis() const { return apis_; }

        void addListener(service_listener *);

        std::shared_ptr<api> createApi(string_type const &);

    protected:
        void notifyCreateApi(std::shared_ptr<api>);
        void notifyDeleteApi(std::shared_ptr<api>);

    private:
        api_container_type apis_;
        string_type title_;
        string_type description_;
        string_type contact_;
        std::vector<service_listener *> listeners_;
    };

    class listener
    {
    public:
        typedef taxii::string_type string_type;

        listener(string_type const &uri, std::shared_ptr<service> s);
        ~listener();

        string_type const &root() const;

    private:
        struct impl;
        impl *pimpl_;
    };
}

#endif
