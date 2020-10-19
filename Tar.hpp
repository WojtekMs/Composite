#pragma once
#include "FileSystemComponent.hpp"

#include <memory>
#include <vector>

using Children = std::vector<std::shared_ptr<FileSystemComponent>>;
using Child = std::shared_ptr<FileSystemComponent>;

class Tar : public FileSystemComponent
{
    Children children_{};
    int size_{300};
    std::string name_{};

   public:
    Tar() = delete;
    Tar(const std::string&, const Child&);
    int getSize() const override;
    void add(const Child&);
    void remove(const Child&);
    const Children& getChildren() const;
};

Tar::Tar(const std::string& name, const Child& child)
:name_(name),
children_({child}) {
    
}

int Tar::getSize() const {
    int totalSize = 0;
    for (const auto& child: children_) {
        totalSize += child->getSize();
    }
    return totalSize * 0.5 + size_;
}
