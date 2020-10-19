#pragma once
#include "FileSystemComponent.hpp"

#include <memory>
#include <vector>
class Directory : public FileSystemComponent
{
    std::vector<std::shared_ptr<FileSystemComponent>> children_{};
    int size_{512};

   public:
    Directory() = default;
    int getSize() const override;
    void add(const std::shared_ptr<FileSystemComponent>&);
    void remove(const std::shared_ptr<FileSystemComponent>&);
    const std::vector<FileSystemComponent>& getChilder() const;
};

int Directory::getSize() const {
    int totalSize = size_;
    for (const auto& component : children_) {
        totalSize += component->getSize();
    }
    return totalSize;
}
