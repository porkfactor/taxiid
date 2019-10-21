#include <taxii/taxii.hpp>
#include <cpprest/http_listener.h>

namespace taxii
{
    service::service()
    {

    }

    service::~service()
    {

    }

    void service::addListener(service::service_listener *l)
    {
        if(l != nullptr)
        {
            listeners_.push_back(l);
        }
    }

    void service::notifyCreateApi(std::shared_ptr<taxii::api> api)
    {
        for(auto i : listeners_)
        {
            i->onCreateApi(api);
        }
    }

    std::shared_ptr<api> service::createApi(service::string_type const &title)
    {
        std::shared_ptr<api> api = std::make_shared<taxii::api>(title, "");

        if(api)
        {
            notifyCreateApi(api);

            apis_.push_back(api);
        }

        return api;
    }
}
