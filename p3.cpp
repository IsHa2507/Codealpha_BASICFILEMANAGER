#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <filesystem>  
#include <cstdlib>     

namespace fs = std::filesystem;
using namespace std;

void listFilesAndDirectories(const string& path) {
    cout << "Listing files and directories in " << path << ":" << endl;
    for (const auto& entry : fs::directory_iterator(path)) {
        cout << entry.path().filename() << endl;
    }
}

void createDirectory(const string& dirName) {
    if (fs::create_directory(dirName)) {
        cout << "Directory created successfully." << endl;
    } else {
        cout << "Failed to create directory." << endl;
    }
}

void copyFile(const string& sourceFile, const string& destinationFile) {
    ifstream source(sourceFile, ios::binary);
    ofstream destination(destinationFile, ios::binary);

    destination << source.rdbuf();

    source.close();
    destination.close();

    cout << "File copied successfully." << endl;
}

void moveFile(const string& sourceFile, const string& destinationFile) {
    if (fs::rename(sourceFile, destinationFile)) {
        cout << "File moved successfully." << endl;
    } else {
        cout << "Failed to move file." << endl;
    }
}

int main() {
    string currentPath = ".";

    while (true) {
        cout << "Current directory: " << currentPath << endl;
        cout << "Options:" << endl;
        cout << "1. List files and directories" << endl;
        cout << "2. Create directory" << endl;
        cout << "3. Copy file" << endl;
        cout << "4. Move file" << endl;
        cout << "5. Change directory" << endl;
        cout << "6. Exit" << endl;
        cout << "Enter your choice: ";

        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                listFilesAndDirectories(currentPath);
                break;
            case 2:
                {
                    string dirName;
                    cout << "Enter directory name: ";
                    cin >> dirName;
                    createDirectory(currentPath + "/" + dirName);
                }
                break;
            case 3:
                {
                    string sourceFile, destinationFile;
                    cout << "Enter source file name: ";
                    cin >> sourceFile;
                    cout << "Enter destination file name: ";
                    cin >> destinationFile;
                    copyFile(currentPath + "/" + sourceFile, currentPath + "/" + destinationFile);
                }
                break;
            case 4:
                {
                    string sourceFile, destinationFile;
                    cout << "Enter source file name: ";
                    cin >> sourceFile;
                    cout << "Enter destination file name: ";
                    cin >> destinationFile;
                    moveFile(currentPath + "/" + sourceFile, currentPath + "/" + destinationFile);
                }
                break;
            case 5:
                {
                    string newDir;
                    cout << "Enter new directory: ";
                    cin >> newDir;
                    if (fs::is_directory(newDir)) {
                        currentPath += "/" + newDir;
                    } else {
                        cout << "Directory does not exist." << endl;
                    }
                }
                break;
            case 6:
                cout << "Exiting..." << endl;
                exit(0);
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << endl;
    }

    return 0;
}
