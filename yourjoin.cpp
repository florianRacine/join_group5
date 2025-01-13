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

// Function to split a string by a delimiter
std::vector<std::string> split(const std::string& line, char delimiter) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;
    while (std::getline(ss, field, delimiter)) {
        fields.push_back(field);
    }
    return fields;
}

// Load the file into a multimap, where key is the first field and value is the second field
std::unordered_multimap<std::string, std::string> loadFile(const std::string& filename, int keyIndex) {
    std::unordered_multimap<std::string, std::string> data;
    std::ifstream file(filename);
    std::string line;
    while (std::getline(file, line)) {
        auto fields = split(line, ',');
        if ((int)fields.size() > keyIndex) {
            if (keyIndex == 0) {
                data.emplace(fields[0], fields[1]);
            } else if (keyIndex == 1) {
                data.emplace(fields[1], fields[0]);
            }
        }
    }
    return data;
}

int main(int argc, char* argv[]) {
    // Check if the correct number of arguments is provided
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " file1 file2 file3 file4\n";
        return 1;
    }


    //std::cout << "load files\n";

    // Step 1: Load the files into multimaps
    // Each multimap allows multiple values for the same key
    //auto file1 = loadFile(argv[1], 0); // Key: First field of File 1, Value: Second field
    //auto file2 = loadFile(argv[2], 0); // Key: First field of File 2, Value: Second field
    //auto file3 = loadFile(argv[3], 0); // Key: First field of File 3, Value: Second field
    //auto file4 = loadFile(argv[4], 0); // Key: First field of File 4, Value: Second field

    // Declare multimaps for storing file data
    std::unordered_multimap<std::string, std::string> file1, file2, file3, file4;

    // Use std::async to load files in parallel
    auto future1 = std::async(std::launch::async, [&]() { return loadFile(argv[1], 0); });
    auto future2 = std::async(std::launch::async, [&]() { return loadFile(argv[2], 0); });
    auto future3 = std::async(std::launch::async, [&]() { return loadFile(argv[3], 0); });
    auto future4 = std::async(std::launch::async, [&]() { return loadFile(argv[4], 0); });

    // Retrieve the results
    file1 = future1.get();
    file2 = future2.get();
    file3 = future3.get();
    file4 = future4.get();


    // Step 2: Perform the join operation
    // We need to join the first three files on their first fields
    // Then join the second field of file3 with the first field of file4

    // The final output should contain:
    // 1. First field of file4
    // 2. First field of file1
    // 3. Second field of file1
    // 4. Second field of file2
    // 5. Second field of file4

    // Step 2.1: Iterate over file1 to start the join process

    //std::cout << "start\n";

    for (const auto& [key1, value1] : file1) {
        // key1: First field of file1
        // value1: Second field of file1

        // Step 2.2: Find all matching records in file2 for key1
        auto range2 = file2.equal_range(key1);
        for (auto it2 = range2.first; it2 != range2.second; ++it2) {
            // it2->first: First field of file2 (matches key1)
            // it2->second: Second field of file2

            // Step 2.3: Find all matching records in file3 for key1
            auto range3 = file3.equal_range(key1);
            for (auto it3 = range3.first; it3 != range3.second; ++it3) {
                // it3->first: First field of file3 (matches key1)
                // it3->second: Second field of file3

                // Step 2.4: Use the second field of file3 as the key to join with file4
                auto range4 = file4.equal_range(it3->second);
                for (auto it4 = range4.first; it4 != range4.second; ++it4) {
                    // it4->first: First field of file4 (matches second field of file3)
                    // it4->second: Second field of file4

                    // Step 3: Output the joined record
                    // Format: [file4.first, file1.first, file1.second, file2.second, file4.second]
                    std::cout << it4->first << ','  // First field of file4
                              << key1 << ','        // First field of file1
                              << value1 << ','      // Second field of file1
                              << it2->second << ',' // Second field of file2
                              << it4->second        // Second field of file4
                              << '\n';
                }
            }
        }
    }
    //std::cout << "end\n";

    // Step 4: Completion
    // The program outputs all matching records in the required format
    // If no matches are found for a particular key, that record is skipped

    return 0;
}
