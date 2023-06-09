#include "envflag/envflag.hpp"
#include "fassert.hpp"
#include <json/writer.h>
#include <memory>
#include <iostream>

IMPORT_JSON_FLAG_WITH_DEFAULT(json_flag_with_default);

using namespace std;

int main() {
    auto x = json_flag_with_default();
    Json::StreamWriterBuilder builder;
    builder["indentation"] = "";
    unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    int ret = writer->write(x, &cout);
    FASSERT(ret == 0)
        (ret);
    return 0;
}
