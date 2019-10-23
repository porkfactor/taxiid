#include <taxii/taxii.hpp>

namespace taxii
{
    std::shared_ptr<taxii::collection> api::createCollection(api::string_type const &c)
    {
        std::shared_ptr<taxii::collection> collection = std::make_shared<taxii::collection>(c, "", "");

        if(collection)
        {
            collections_.push_back(collection);
        }

        return collection;
    }
}
