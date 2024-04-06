#include <iostream>
#include "fstream"
#include "request.h"

using rq = rqst::request;
using namespace std;

int main() {

    ifstream file("settings.json");
    if(!file.good()) {
        JSON defaultSettings = {
                {"console_only", true},
                {"nsfw", false}
        };

        ofstream out("settings.json");
        out << setw(4) << defaultSettings;

        cout << "Created Configuration File" << endl;
    }

    JSON read = rq::send("https://astolfo.poligon.lgbt/api/sfw");
    read.dump(4);
    cout << read["url"];
    return 0;
}
