#include "load_file.h"

#include <fstream>

#include "exception.h"

std::string loadFile(const std::string& path) {
    std::ifstream stream(path);

    if (!stream.is_open()) throw Exception("loadFile: the file \"" + path + "\" doesn't exist");

    std::string source;

    const int size = 1024;
    char buffer[size];

    while (stream) {
        stream.read(buffer, size);

        source.append(buffer, stream.gcount());
    }

    return source;
}
