#include "Directory.hpp"
#include "File.hpp"
#include "MusicFile.hpp"
#include <iostream>

int main() {
    auto dir = std::make_shared<Directory>("dir");
    auto file = std::make_shared<File>("file", 30);

    dir->add(std::make_shared<Directory>("dir2"));    
    dir->add(std::make_shared<File>("file1", 300));

    Directory anotherDir("bigDir");
    anotherDir.add(dir);
    anotherDir.add(file);
    anotherDir.add(std::make_shared<MusicFile>("superSong", 3.32));
    
    dir->getSize();
    file->getSize();
    for (const auto& component : anotherDir.getChildren()) {
        std::cout << component->getSize() << '\n';
    }
}
