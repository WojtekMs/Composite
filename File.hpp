#pragma once

#include <string>

class File {
    std::string name_{};
    int size_{0};
    public:
    File() = default;
    File(const std::string&, int size = 0);
    const std::string& getName() const;
    int getSize() const;
};

std::shared_ptr<File> make_file(const std::string& fileName = "", int fileSize = 0) {
    return std::make_shared<File>(fileName, fileSize);
}

File::File(const std::string& fileName, int size)
:name_(fileName),
size_(size) {

}

const std::string& File::getName() const {
    return name_;
}

int File::getSize() const {
    return size_;
}
