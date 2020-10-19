#pragma once
#include "FileSystemComponent.hpp"

class File : public FileSystemComponent
{
    int size_{};

   public:
    File() = default;
    explicit File(int);
    int getSize() const override;
};

File::File(int size)
:size_(size) {

}

int File::getSize() const {
    return size_{};
}

