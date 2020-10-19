#pragma once

#include <algorithm>
#include <memory>
#include <numeric>
#include <vector>

#include "File.hpp"
class Directory {
    std::vector<std::shared_ptr<File>> files_{};
    std::vector<std::shared_ptr<Directory>> directories_{};
    int size_{512};
    std::string name_{"dir"};

    int getAllFilesSize() const;
    public:
    Directory() = default;
    Directory(const std::string&);
    void add(const std::shared_ptr<File>&);
    void add(const std::shared_ptr<Directory>&);
    void remove(const std::string&);
    const std::vector<std::shared_ptr<File>> getFiles() const;
    const std::vector<std::shared_ptr<Directory>> getDirectories() const;
    int getSize() const;
    const std::string& getName() const;

};


std::shared_ptr<Directory> make_directory(const std::string& dirName) {
    return std::make_shared<Directory>(dirName);
}

std::shared_ptr<Directory> make_directory(const Directory& dir) {
    return std::make_shared<Directory>(dir);
}

Directory::Directory(const std::string& name)
:name_(name) {

}

void Directory::add(const std::shared_ptr<File>& file) {
    if (!file) {
        return;
    }
    if (file->getName().empty()) {
        return;
    }
    files_.emplace_back(file);
}

void Directory::add(const std::shared_ptr<Directory>& directory) {
    if (!directory) {
        return;
    }
    if (directory->getName().empty()) {
        return;
    }
    directories_.emplace_back(directory);
}

void Directory::remove(const std::string& fileName) {
    files_.erase(std::remove_if(files_.begin(), files_.end(), 
    [&fileName](const auto& file)
    {
        return file->getName() == fileName;
    }), files_.end());
}

const std::vector<std::shared_ptr<File>> Directory::getFiles() const {
    return files_;
}

const std::string& Directory::getName() const {
    return name_;
}

int Directory::getAllFilesSize() const {
    return std::accumulate(files_.begin(), files_.end(), size_,
    [=](int current_sum, const std::shared_ptr<File>& rhs) -> int
    {
        return current_sum + rhs->getSize();
    });
}

int Directory::getSize() const {
    int totalSize{};
    totalSize += getAllFilesSize();
    for (const auto& dir : directories_) {
        totalSize += dir->getSize();
    }
    return totalSize;
}
