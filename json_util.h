//
// Created by verifiedfemboy on 07.04.24.
//


#ifndef ASTOLFO_DOWNLOADER_JSON_UTIL_H
#define ASTOLFO_DOWNLOADER_JSON_UTIL_H

#endif //ASTOLFO_DOWNLOADER_JSON_UTIL_H
#include "request.h"
#include <fstream>
#include <iostream>

using namespace std;

void saveJSON(const JSON& json) {
    ifstream file("settings.json");
    if(file.good()) {
        ofstream out("settings.json");
        out << setw(4) << json;
    }
}
