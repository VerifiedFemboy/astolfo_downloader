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
        //writes a stream to string
        static size_t WriteCallback(void *contents, size_t size, size_t nmemb, std::string *output) {
            output->append((char *)contents, size * nmemb);
            return size * nmemb;
        }

        /*
         * sends a request and gets json
         * Example: nlohmann::json read = rq::send("https://astolfo.poligon.lgbt/api/sfw");
         * or
         * JSON read = JSON::parse(rq::send("https://astolfo.poligon.lgbt/api/" + option));
         * */
        static std::string send(const std::string& url) {
            std::string readBuffer;
            CURL* curl = curl_easy_init();
            if (curl) {
                curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
                curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
                curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

                curl_easy_perform(curl);
                curl_easy_cleanup(curl);
            }
            return readBuffer;
        }

        static void downloadFile(const std::string& url, const std::string& path, const std::string& fileName) {
            FILE* file;
            file = fopen((path + "/" + fileName).c_str(), "wb");
            if(file) {
                std::string data = send(url);
                fwrite(data.c_str(), 1, data.size(), file);
                fclose(file);
            }
        }
    };

    static std::string randomStr() {
        const std::string characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
        const int length = 6;
        std::string result;

        srand(static_cast<unsigned int>(time(nullptr)));

        for (int i = 0; i < length; ++i) {
            int randomIndex = rand() % characters.length();
            result += characters[randomIndex];
        }

        return result;
    }

} // rqst

#endif //ASTOLFO_DOWNLOADER_REQUEST_H
