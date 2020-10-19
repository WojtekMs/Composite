#pragma once

class FileSystemComponent
{
   public:
    virtual ~FileSystemComponent() = default;
    virtual int getSize() const = 0;
};
