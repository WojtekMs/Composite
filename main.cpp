#include <memory>

#include "Directory.hpp"
#include "File.hpp"
#include "Tar.hpp"
int main() {
    auto directory = std::make_shared<Directory>("dir");
    directory->add(std::make_shared<File>("firstFileName", 300));
    directory->add(std::make_shared<Directory>("defaultDirectoryName"));
    directory->add(std::make_shared<File>("secondFileName", 250));
    
    auto file = std::make_shared<File>("anotherFile", 100);
    auto archive = std::make_shared<Tar>("defaultTarName", directory);

    directory->add(archive);
    
    archive->getSize();
    directory->getSize();
}
