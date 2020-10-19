#include "Directory.hpp"
#include "File.hpp"

int main() {
    auto dir = std::make_shared<Directory>("dir");
    auto file = std::make_shared<File>("file", 30);
    dir->add(std::make_shared<Directory>("dir2"));    
    dir->add(std::make_shared<File>("file1", 300));
    Directory anotherDir("bigDir");
    anotherDir.add(dir);
    anotherDir.add(file);
    dir->getSize();
    file->getSize();
}
