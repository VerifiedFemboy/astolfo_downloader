//
// Created by verifiedfemboy on 06.04.24.
//

#ifndef ASTOLFO_DOWNLOADER_REQUEST_H
#define ASTOLFO_DOWNLOADER_REQUEST_H

#include "iostream"
#include "curl/curl.h"
#include "nlohmann/json.hpp"

using JSON = nlohmann::json;

namespace rqst {
    class request {
    public:
        //writes stream to string
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
            ((std::string*)userp)->append((char*)contents, size * nmemb);
            return size * nmemb;
        }

        /*
         * sends a request and gets json
         * Example: nlohmann::json read = rq::send("https://astolfo.poligon.lgbt/api/sfw");
         * or
         * JSON read = rq::send("https://astolfo.poligon.lgbt/api/sfw");
         * */
        static JSON send(const std::string& url) {
            std::string readBuffer;
            CURL* curl = curl_easy_init();
            if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

                curl_easy_perform(curl);
                curl_easy_cleanup(curl);
            }
            return JSON::parse(readBuffer);
        }

        //TODO: make better getter?
        /*static std::string get(const std::string& target, const JSON& json) {
            return json[target];
        }*/
    };

} // rqst

#endif //ASTOLFO_DOWNLOADER_REQUEST_H
