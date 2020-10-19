#include "Directory.hpp"

#include "gtest/gtest.h"
class DirectoryTest : public ::testing::Test
{
   protected:
    Directory dir;

    const std::string firstFileName = "first";
    const std::string secondFileName = "second";
    const int firstFileSize = 100;
    const int secondFileSize = 250;

    const int defaultDirectorySize = dir.getSize();
    const std::string defaultDirectoryName = "directory";
    const std::string firstDirectoryName = "firstDir";
    const std::string secondDirectoryName = "secondDir";
};

TEST_F(DirectoryTest, filesCanBeAddedToDirectory)
{
    dir.add(std::make_shared<File>("file"));
    dir.add(std::make_shared<File>("anotherFile"));
    constexpr int expectedDirSize = 2;
    EXPECT_EQ(dir.getFiles().size(), expectedDirSize);
}

TEST_F(DirectoryTest, filesCanBeRemovedFromDirectory)
{
    dir.add(make_file(firstFileName));
    dir.add(make_file(secondFileName));
    dir.remove(firstFileName);
    constexpr int expectedDirSize = 1;
    constexpr char expectedFileName[] = "second";
    EXPECT_EQ(dir.getFiles().size(), expectedDirSize);
    EXPECT_EQ(dir.getFiles().front()->getName(), expectedFileName);
}

TEST_F(DirectoryTest, emptyDirectorySizeShouldBe512) {
    constexpr int expectedDirSize = 512;
    EXPECT_EQ(dir.getSize(), expectedDirSize);
}

TEST_F(DirectoryTest, directoryShouldCountSizeOfContainingFiles) {
    dir.add(make_file(firstFileName, firstFileSize));
    dir.add(make_file(secondFileName, secondFileSize));
    EXPECT_EQ(dir.getSize(), defaultDirectorySize + firstFileSize + secondFileSize);
}

TEST_F(DirectoryTest, directoryShouldCountSizeOfOtherDirs) {
    Directory anotherDir;
    Directory secondDir(secondDirectoryName);
    anotherDir.add(make_directory(firstDirectoryName));
    anotherDir.add(make_file(firstFileName, firstFileSize));

    dir.add(make_directory(secondDir));
    dir.add(make_directory(anotherDir));

    int totalDirCount = 4;
    int expectedDirSize = defaultDirectorySize * totalDirCount + firstFileSize;
    EXPECT_EQ(dir.getSize(), expectedDirSize);
}
