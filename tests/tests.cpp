#include "Directory.hpp"
#include "File.hpp"
#include "Tar.hpp"

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

    const std::string defaultTarName = "tarArchive";
    const int defaultTarSize = 300;
};

TEST_F(DirectoryTest, filesCanBeAddedToDirectory)
{
    dir.add(std::make_shared<File>(firstFileName));
    dir.add(std::make_shared<File>(secondFileName));
    constexpr int expectedDirSize = 2;
    EXPECT_EQ(dir.getChildren().size(), expectedDirSize);
}

TEST_F(DirectoryTest, filesCanBeRemovedFromDirectory)
{
    auto fileToRemove = std::make_shared<File>(secondFileName);
    dir.add(std::make_shared<File>(firstFileName, firstFileSize));
    dir.add(fileToRemove);
    dir.remove(fileToRemove);
    constexpr int expectedDirSize = 1;
    EXPECT_EQ(dir.getChildren().size(), expectedDirSize);
    EXPECT_EQ(dir.getChildren().front()->getSize(), firstFileSize);
}

TEST_F(DirectoryTest, emptyDirectorySizeShouldBe512)
{
    constexpr int expectedDirSize = 512;
    EXPECT_EQ(dir.getSize(), expectedDirSize);
}

TEST_F(DirectoryTest, directoryShouldCountSizeOfContainingFiles)
{
    dir.add(std::make_shared<File>(firstFileName, firstFileSize));
    dir.add(std::make_shared<File>(secondFileName, secondFileSize));
    EXPECT_EQ(dir.getSize(), defaultDirectorySize + firstFileSize + secondFileSize);
}

TEST_F(DirectoryTest, directoryShouldCountSizeOfOtherDirs)
{
    Directory anotherDir;
    Directory secondDir(secondDirectoryName);
    anotherDir.add(std::make_shared<Directory>(firstDirectoryName));
    anotherDir.add(std::make_shared<File>(firstFileName, firstFileSize));

    dir.add(std::make_shared<Directory>(secondDir));
    dir.add(std::make_shared<Directory>(anotherDir));

    int totalDirCount = 4;
    int expectedDirSize = defaultDirectorySize * totalDirCount + firstFileSize;
    EXPECT_EQ(dir.getSize(), expectedDirSize);
}

TEST_F(DirectoryTest, tarShouldReturnHalfSizeOfWhatItContains)
{
    auto directory = std::make_shared<Directory>(firstDirectoryName);
    directory->add(std::make_shared<File>(firstFileName, firstFileSize));
    directory->add(std::make_shared<Directory>(defaultDirectoryName));
    directory->add(std::make_shared<File>(secondFileName, secondFileSize));

    auto archive = std::make_shared<Tar>(defaultTarName, directory);
    int totalDirectoryCount = 2;
    int expectedArchiveSize =
        (defaultDirectorySize * totalDirectoryCount + firstFileSize + secondFileSize) * 0.5 + defaultTarSize;
    EXPECT_EQ(archive->getSize(), expectedArchiveSize);
}
