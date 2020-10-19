#pragma once
#include "FileSystemComponent.hpp"

#include <algorithm>
#include <memory>
#include <vector>

using Children = std::vector<std::shared_ptr<FileSystemComponent>>;
using Child = std::shared_ptr<FileSystemComponent>;

class Directory : public FileSystemComponent
{
    Children children_{};
    int size_{512};
    std::string name_{};

   public:
    Directory() = default;
    Directory(const std::string&);
    int getSize() const override;
    void add(const Child&);
    void remove(const Child&);
    const Children& getChildren() const;
};

Directory::Directory(const std::string& name)
:name_(name) {

}

int Directory::getSize() const {
    int totalSize = size_;
    for (const auto& component : children_) {
        totalSize += component->getSize();
    }
    return totalSize;
}

void Directory::add(const Child& component) {
    if (!component) {
        return;
    }
    children_.emplace_back(component);
}

void Directory::remove(const Child& component) {
    children_.erase(std::remove(children_.begin(), children_.end(), component));
}

const Children& Directory::getChildren() const {
    return children_;
}
