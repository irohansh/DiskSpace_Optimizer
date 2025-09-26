#include <iostream>
#include <filesystem>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <openssl/evp.h>
#include <iomanip>
#include <sstream>

using namespace std;
namespace fs = filesystem;

string get_file_hash(const fs::path& file_path) {
    unsigned char hash[EVP_MAX_MD_SIZE]; 
    unsigned int hash_length;
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new(); 
    if (mdctx == nullptr) {
        cerr << "Could not create EVP_MD_CTX" << endl;
        return "";
    }
    
    const EVP_MD* md = EVP_sha256(); 
    EVP_DigestInit_ex(mdctx, md, nullptr); 
    
    try {
        ifstream file(file_path, ios::binary);
        if (!file.is_open()) {
            throw runtime_error("Could not open file");
        }
        
        char buffer[4096];
        while (file.read(buffer, sizeof(buffer))) {
            EVP_DigestUpdate(mdctx, buffer, file.gcount()); 
        }
        EVP_DigestUpdate(mdctx, buffer, file.gcount()); 
        
        EVP_DigestFinal_ex(mdctx, hash, &hash_length); 
        
        ostringstream hex_stream;
        for (unsigned int i = 0; i < hash_length; ++i) {
            hex_stream << hex << setw(2) << setfill('0') << (int)hash[i];
        }
        EVP_MD_CTX_free(mdctx);
        return hex_stream.str(); 
    } catch (const exception& e) {
        cerr << "Could not read file " << file_path << ": " << e.what() << endl;
        EVP_MD_CTX_free(mdctx);
        return "";
    }
}

vector<vector<fs::path>> find_duplicate_files(const fs::path& root_directory) {
    unordered_map<string, vector<fs::path>> files_hash; 
    vector<vector<fs::path>> duplicates;
    
    for (const auto& entry : fs::recursive_directory_iterator(root_directory)) {
        if (fs::is_regular_file(entry)) {
            string file_hash = get_file_hash(entry.path()); 
            if (!file_hash.empty()) {
                files_hash[file_hash].push_back(entry.path());
            }
        }
    }
    
    for (const auto& [_, file_paths] : files_hash) {
        if (file_paths.size() > 1) {
            duplicates.push_back(file_paths); 
        }
    }
    return duplicates;
}

void move_duplicates(const vector<vector<fs::path>>& duplicates, const fs::path& destination) {
    fs::create_directories(destination); 
    vector<fs::path> files_to_delete; 
    
    for (const auto& file_group : duplicates) {
        cout << "\nFound the following duplicate files:" << endl;
        for (size_t i = 0; i < file_group.size(); ++i) {
            cout << i + 1 << ": " << file_group[i] << endl;
        }
        cout << "0: To Skip the current file group" << endl;
        
        int choice;
        cout << "\nEnter the number of the file you want to keep (1-" << file_group.size() << "): ";
        cin >> choice;
        cout << endl;
        
        if (choice == 0) continue;
        
        while (choice < 1 || choice > file_group.size()) {
            cout << "Invalid choice. Please enter a number between 1 and " << file_group.size() + 1 << ": ";
            cin >> choice;
        }
        
        for (size_t i = 0; i < file_group.size(); ++i) {
            if (i + 1 != choice) {
                try {
                    fs::path destination_path = destination / file_group[i].filename();
                    fs::rename(file_group[i], destination_path); // Move file
                    cout << "Moved " << file_group[i] << " to " << destination_path << endl;
                    files_to_delete.push_back(destination_path);
                } catch (const exception& e) {
                    cerr << "Could not move file " << file_group[i] << ": " << e.what() << endl;
                }
            }
        }
    }
    
    cout << "\nDo you want to delete the moved duplicate files? (y/n): ";
    char confirm;
    cin >> confirm;
    
    if (confirm == 'y' || confirm == 'Y') {
        for (const auto& file : files_to_delete) {
            try {
                fs::remove(file); 
                cout << "Deleted " << file << endl;
            } catch (const exception& e) {
                cerr << "Could not delete file " << file << ": " << e.what() << endl;
            }
        }
    } else {
        cout << "Duplicate files have been retained in " << destination << endl;
    }
}

int main() {
    cout << "\n\n-----------------------------------\n";
    cout << "Welcome to diskSpace Optimizer";
    cout << "\n-----------------------------------\n\n";
    
    string root_directory;
    string destination_directory;
    
    cout << "Enter the root directory to search for duplicate files: ";
    getline(cin, root_directory);
    
    cout << "Enter the destination directory for duplicate files: ";
    getline(cin, destination_directory);
    
    cout << "\nScanning for duplicate files.....\n" << endl;
    
    auto duplicates = find_duplicate_files(root_directory);
    
    if (!duplicates.empty()) {
        cout << "Found " << duplicates.size() << " groups of duplicate files." << endl;
        move_duplicates(duplicates, destination_directory);
        cout << "\nDuplicate files have been processed." << endl;
    } else {
        cout << "No duplicate files found." << endl;
    }
    return 0;
}

