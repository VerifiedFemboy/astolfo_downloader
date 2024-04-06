#include <iostream>
#include "fstream"
#include "request.h"
#include "os_lib.h"
#include "ncurses.h"

using rq = rqst::request;
using namespace std;

void download() {
    JSON read = rq::send("https://astolfo.poligon.lgbt/api/sfw");
    read.dump(4);
    cout << read["url"];
}

void settings() {
    clearScreen();

    ifstream file("settings.json");
    JSON settings;
    file >> settings;

    printw("settings: \n");
    printw("console only: %s\n", settings["console_only"].dump().c_str());
    printw("nsfw: %s\n", settings["nsfw"].dump().c_str());
    printw("\n[1] console_only on/off [2] nsfw on/off [Q] back");
    refresh();
}

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

    initscr();
    cbreak();
    noecho();
    attrset(A_NORMAL);
    printw("Do you want download or change settings?\n");
    refresh();
    printw("[1] download [2] settings");
    refresh();

    while (true) {
        int key = getch();

        if (key == '1') {
            download();
            break;
        }
        if (key == '2') {
            settings();
            break;
        }
    }
    return 0;
}
