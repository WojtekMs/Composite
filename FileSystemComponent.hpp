#pragma once

class FileSystemComponent {
    virtual ~FileSystemComponent() = default;
    virtual unsigned int getSize() = 0;
};
