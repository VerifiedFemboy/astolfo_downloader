cmake_minimum_required(VERSION 3.27)
project(astolfo_downloader)

set(CMAKE_CXX_STANDARD 17)

add_executable(astolfo_downloader main.cpp
        request.h)

find_package(unofficial-curlpp CONFIG REQUIRED)
find_package(nlohmann_json CONFIG REQUIRED)

target_link_libraries(astolfo_downloader PRIVATE unofficial::curlpp::curlpp)
target_link_libraries(astolfo_downloader PRIVATE nlohmann_json::nlohmann_json)
