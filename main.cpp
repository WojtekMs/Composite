#include "Directory.hpp"
#include "File.hpp"

int main() {
    Directory dir("example");
    dir.add(make_file("file1.txt", 150));
    dir.add(make_file("file2.txt", 350));
    File fil("bookaro");
    fil.getSize();
    dir.getSize();    
}
