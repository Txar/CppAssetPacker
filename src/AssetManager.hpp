#pragma once

#include <map>
#include <string>

class AssetManager {
private:
    static std::map<std::string, std::string> _assets;
    static std::map<std::string, const unsigned char[]> assets;
    static bool initialized;

public:
    static void initialize();
    static bool isInitialized();

    static std::string AssetManager::base64_decode(const std::string &in);

    static std::string getAsset(std::string name);
};