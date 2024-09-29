#include <fstream>
#include <iostream>
#include <vector>

using namespace std;
using uchar = unsigned char;


static std::string base64_encode(const std::string &in) {

    std::string out;

    int val = 0, valb = -6;
    for (uchar c : in) {
        val = (val << 8) + c;
        valb += 8;
        while (valb >= 0) {
            out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(val>>valb)&0x3F]);
            valb -= 6;
        }
    }
    if (valb>-6) out.push_back("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((val<<8)>>(valb+8))&0x3F]);
    while (out.size()%4) out.push_back('=');
    return out;
}

void throwFileNotFound(string filename) {
    cout << "File " << filename << " not found or inaccesible! Check your configs and permissions.\n";
    throw exception();
}

vector<char> ReadAllBytes(string filename)
{
    ifstream f(filename, ios::binary|ios::ate);

    if (!f.is_open()) {
        throwFileNotFound(filename);
    }

    ifstream::pos_type pos = f.tellg();

    if (pos == 0) {
        return vector<char>{};
    }

    vector<char> result(pos);

    f.seekg(0, ios::beg);
    f.read(&result[0], pos);

    return result;
}

vector<string> ReadAllLines(string filename) {
    ifstream f(filename);
    if (!f.is_open()) {
        throwFileNotFound(filename);
    }

    vector<string> lines = {};
    string line;
    do {
        getline(f, line);
        lines.push_back(line);
    } while (!f.eof());
    return lines;
}

string BytesToString(vector<char> data) {
    string out = "";
    for (auto i : data) {
        out += i;
    }
    return out;
}

void OutputToStream(vector<char> data, ofstream &of) {
    for (auto i : data) {
        of << i;
    }
}

int main() {
    string assetsHome = ReadAllLines("directories").at(0);
    auto paths = ReadAllLines("files");
    //auto data = ReadAllBytes("samples/run.png");
    //ofstream of("output.png", ios::out|ios::binary);
    //string str = "";
    string firstHalf = "#include \"AssetManager.hpp\"\n#include <vector>\nstd::map<std::string, std::string> AssetManager::assets;void AssetManager::initialize() {assets = {};";
    string secondHalf = "}std::string AssetManager::base64_decode(const std::string &in) {std::string out;std::vector<int> T(256,-1);for (int i=0; i<64; i++) T[\"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/\"[i]] = i;int val=0, valb=-8;for (unsigned char c : in) {if (T[c] == -1) break;val = (val << 6) + T[c];valb += 6;if (valb >= 0) {out.push_back(char((val>>valb)&0xFF));valb -= 8;}}return out;}std::string AssetManager::getAsset(std::string filename) {return base64_decode(assets.at(filename));}";

    string middle = "";

    ofstream of("AssetManager.cpp");

    if (!of.is_open()) {
        std::cout << "Failed to create output file.\n";
        return -1;
    }

    ofstream of2("output");
    of << firstHalf;
    for (auto path : paths) {
        auto bytes = ReadAllBytes(assetsHome + "/" + path);
        of2 << BytesToString(bytes);
        of << "assets.insert({\"" << path << "\", \"";
        of << base64_encode(BytesToString(bytes));
        of << "\"});";
    }
    of << secondHalf;
    of.close();
    
    //cout << str;
    //of.close();

    return 0;
}