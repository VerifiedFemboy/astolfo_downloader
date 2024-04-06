#include <iostream>
#include "request.h"

using rq = rqst::request;
using namespace std;

int main() {
    JSON read = rq::send("https://astolfo.poligon.lgbt/api/sfw");
    read.dump(4);
    cout << read["url"];
    return 0;
}
