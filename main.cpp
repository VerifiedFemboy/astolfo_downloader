#include <iostream>
#include <fstream>
#include <csignal>
#include "request.h"
#include "os_lib.h"
#include "json_util.h"

using rq = rqst::request;
using namespace std;

JSON GLOBAL_SETTINGS;

void menu();
void download();
void settings_menu();
void handle_signal(int signal);
void load_settings();


int main() {
    signal(SIGINT, handle_signal);

    ifstream file("settings.json");
    if (!file.good()) {
        JSON defaultSettings = {
                {"console_only", true},
                {"nsfw", false},
                {"path", getHomeDirectory()}
        };

        ofstream out("settings.json");
        out << setw(4) << defaultSettings;

        cout << "Created Configuration File" << endl;
        return 0;
    }

    load_settings();

    menu();
    return 0;
}

void handle_signal(int signal) {
    cout << "Received SIGINT. Exiting..." << endl;
    exit(signal);
}

void menu() {
    clearScreen();
    cout << "Do you want to download or change settings?\n";
    cout << "[1] Download [2] Settings [q] Quit" << endl;
    char ch;
    cout << "Enter: ";
    cin >> ch;
    switch (ch) {
        case '1':
            download();
            break;
        case '2':
            settings_menu();
            break;
        case 'q':
            cout << "Exiting..." << endl;
            exit(0);
        default:
            cout << "[!] Unknown command" << endl;
            sleep(1);
            menu();
            break;
    }
}

void download() {
    string option = GLOBAL_SETTINGS["nsfw"] ? "nsfw" : "sfw";
    JSON read = JSON::parse(rq::send("https://astolfo.poligon.lgbt/api/" + option));
    string url = read["url"];
    cout << "Downloading: " << url << endl;

    string filename = rqst::randomStr();
    string path = GLOBAL_SETTINGS["path"];
    rq::downloadFile(url, path, filename);

    cout << "Download completed!" << endl;
    cout << "Do you want generate again? [Y/n]" << endl;
    cout << "Enter: ";
    char input;
    cin >> input;
    switch (input) {
        case 'Y':
        case 'y':
            download();
            break;
        default:
            menu();
            break;
    }
//    system(("xdg-open " + path + "/" + filename).c_str()); @TODO: fix this
}

void settings_menu() {
    clearScreen();

    ifstream file("settings.json");
    JSON settings;
    file >> settings;

    cout << "Settings:" << endl;
    cout << "Console only: " << settings["console_only"].dump().c_str() << endl;
    cout << "NSFW: " << settings["nsfw"].dump().c_str() << endl;
    cout << "PATH: " << settings["path"].dump().c_str() << endl;
    cout << "\n[1] Console only on/off [2] NSFW on/off [3] change path [q] Back\n";

    char ch;
    cout << "Enter: ";
    cin >> ch;
    switch (ch) {
        case '1':
            settings["console_only"] = !settings["console_only"];
            GLOBAL_SETTINGS = settings;
            saveJSON(GLOBAL_SETTINGS);
            settings_menu();
            break;
        case '2':
            settings["nsfw"] = !settings["nsfw"];
            GLOBAL_SETTINGS = settings;
            saveJSON(GLOBAL_SETTINGS);
            settings_menu();
            break;
        case '3': {
            clearScreen();
            cout << "Enter new path: ";
            cin.ignore();
            string newPath;
            getline(cin, newPath);
            settings["path"] = newPath;
            GLOBAL_SETTINGS = settings;
            saveJSON(GLOBAL_SETTINGS);
            settings_menu();
            break;
        }
        case 'q':
            menu();
            break;
        default:
            cout << "[!] Unknown command" << endl;
            sleep(1);
            settings_menu();
            break;
    }
}

void load_settings() {
    ifstream file("settings.json");
    JSON current_settings;
    file >> current_settings;
    GLOBAL_SETTINGS = current_settings;
}


