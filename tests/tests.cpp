#include "gtest/gtest.h"
#include "Directory.hpp"
class DirectoryTest : public ::testing::Test {
};

TEST(DirectoryTest, directoryCanBeCreated) {
    Directory empty;
}
