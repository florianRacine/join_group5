#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>

#include <thread>
#include <mutex>
#include <future>

std::unordered_multimap<std::string, std::string> loadFile(const std::string& filename) {
    std::unordered_multimap<std::string, std::string> data;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
	std::string key, value;
        std::getline(ss, key, ',');
        std::getline(ss, value);
	data.emplace(key, value);
    }

    return data;
}

std::vector<std::pair<std::string, std::string>> loadFileToVector(const std::string& filename) {
    std::vector<std::pair<std::string, std::string>> data;
    std::ifstream file(filename);
    std::string line;

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string key, value;
        if (std::getline(ss, key, ',') && std::getline(ss, value)) {
            data.emplace_back(key, value);
        }
    }

    return data;
}

int main(int argc, char* argv[]) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " file1 file2 file3 file4\n";
        return 1;
    }

    std::ios_base::sync_with_stdio(false);
    std::cout.tie(nullptr);

    std::ostringstream outputBuffer;
    size_t bufferLimit = 1000;

    auto file1 = loadFile(argv[1]);
    auto file2 = loadFile(argv[2]);
    auto file3 = loadFile(argv[3]);
    auto file4 = loadFile(argv[4]);

    for (const auto& [key1, value1] : file1) {
        auto range2 = file2.equal_range(key1);
	auto range3 = file3.equal_range(key1);
        for (auto it2 = range2.first; it2 != range2.second; ++it2) {
            for (auto it3 = range3.first; it3 != range3.second; ++it3) {
                auto range4 = file4.equal_range(it3->second);
                for (auto it4 = range4.first; it4 != range4.second; ++it4) {
                    outputBuffer << it4->first << ',' << key1 << ',' << value1 << ',' 
                                 << it2->second << ',' << it4->second << '\n';
                    if (outputBuffer.tellp() >= static_cast<std::streamoff>(bufferLimit)) {
                        std::cout << outputBuffer.str();
                        outputBuffer.str("");
                        outputBuffer.clear();
                    }                
		}
            }
        }
    }
    if (outputBuffer.tellp() > 0) {
        std::cout << outputBuffer.str();
    }
    return 0;
}
