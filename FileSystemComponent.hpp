#pragma once

class FileSystemComponent {
    virtual ~FileSystemComponent() = default;
    virtual int getSize() const = 0;
};
