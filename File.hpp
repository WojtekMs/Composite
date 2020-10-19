#pragma once
#include "FileSystemComponent.hpp"

class File : public FileSystemComponent //Leaf
{
    int size_{};
    std::string name_{};

   public:
    File() = default;
    explicit File(const std::string&, int size = 0);
    int getSize() const override;
};

File::File(const std::string& name, int size)
:size_(size),
name_(name) {

}

int File::getSize() const {
    return size_;
}

