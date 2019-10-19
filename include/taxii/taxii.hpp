#ifndef TAXII_HPP_
#define TAXII_HPP_

namespace taxii
{
    static constexpr char const *TAXII_1_MEDIA_TYPE = "";
    static constexpr char const *TAXII_2_MEDIA_TYPE = "application/vnd.oasis.taxii+json";
    static constexpr char const *STIX_2_MEDIA_TYPE = "application/vnd.oasis.stix+json";

    static constexpr char const *TAXII_2_ENDPOINT = "/taxii";

    class basic_taxii_endpoint
    {

    };

    class basic_discovery_endpoint : public basic_taxii_endpoint
    {

    };

    class basic_status_endpoint : public basic_taxii_endpoint
    {

    };
}

#endif
