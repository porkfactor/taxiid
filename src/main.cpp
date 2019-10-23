#include <memory>
#include <taxii/taxii.hpp>
#include "log.hpp"

/*
 * 1/ create service (the content thinger)
 * 2/ create listener (base uri, service)
 *     - create /taxii endpoint
 * 2/ create api(s)
 *     - create /<api> endpoint (GET)
 *     - create /<api>/status endpoint (GET)
 *     - create /<api>/collections endpoint (GET)
 * 3/ create collection(s)
 *     - create /<api>/collections/<id> endpoint (GET)
 *     - create /<api>/collections/<id>/objects endpoint (GET, POST)
 *     - create /<api>/collections/<id>/manifest endpoint (GET)
 * 
 */

int main(int argc, const char * argv[]) {
    spdlog::set_default_logger(spdlog::stdout_color_mt("console"));

    try
    {
        std::shared_ptr<taxii::service> ts(std::make_shared<taxii::service>("test", "test service"));
        taxii::listener tl("http://mimsy.local:6502", ts);

        ts->createApi("abc");
        ts->createApi("xyz");
//        ts->createApi("xyz")->createCollection("wine");

        while(1)
        {
            sleep(100);
        }
    }
    catch(std::exception &e)
    {
        spdlog::error("exception: {}", e.what());
    }
    catch(...)
    {
        // RuntimeUtils::printStackTrace();
    }

    return 0;
}