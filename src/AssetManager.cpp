#include "AssetManager.hpp"
#include <sstream>
#include <vector>

std::map<std::string, const unsigned char[]> AssetManager::assets;

bool AssetManager::initialized = false;

bool AssetManager::isInitialized() {
    return initialized;
}

void AssetManager::initialize() {
    initialized = true;
    assets.insert("", "");
}

// std::string AssetManager::base64_decode(const std::string &in) {

//     std::string out;

//     std::vector<int> T(256,-1);
//     for (int i=0; i<64; i++) T["ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[i]] = i;

//     int val=0, valb=-8;
//     for (unsigned char c : in) {
//         if (T[c] == -1) break;
//         val = (val << 6) + T[c];
//         valb += 6;
//         if (valb >= 0) {
//             out.push_back(char((val>>valb)&0xFF));
//             valb -= 8;
//         }
//     }
//     return out;
// }

std::string hex_decode(const unsigned char *data) {
    std::stringstream ss;
    for (unsigned int i = 0; i < sizeof(data); i++) {
        ss << data[i];
    }
    return ss.str();
}

std::string AssetManager::getAsset(std::string filename) {
    return hex_decode(assets.at(filename));
}