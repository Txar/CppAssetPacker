#pragma once

#include <map>
#include <string.h>


class AssetManager {
private:
    static std::map<std::string, std::string> assets;

public:
    static void initialize();

    static std::string base64_decode(const std::string &in);

    static std::string getAsset(std::string name);
};