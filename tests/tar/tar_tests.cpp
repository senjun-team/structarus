#include <filesystem>
#include <gtest/gtest.h>
#include <sstream>

#include "include/structarus/tar_creator.hpp"
#include "include/structarus/tar_info.hpp"

using namespace tar;
namespace fs = std::filesystem;

TEST(TarHeader, BasicConstruction) {
  detail::Header header;
  EXPECT_EQ(header.name.size(), 100u);
  EXPECT_EQ(header.mode.size(), 8u);
  EXPECT_EQ(header.uid.size(), 8u);
  EXPECT_EQ(header.gid.size(), 8u);
  EXPECT_EQ(header.size.size(), 12u);
  EXPECT_EQ(header.mtime.size(), 12u);
  EXPECT_EQ(header.checksum.size(), 8u);
  EXPECT_EQ(header.typeflag, '0');
  EXPECT_EQ(header.linkname.size(), 100u);
  EXPECT_EQ(header.magic.size(), 6u);
  EXPECT_EQ(header.version.size(), 2u);
  EXPECT_EQ(header.uname.size(), 32u);
  EXPECT_EQ(header.gname.size(), 32u);
  EXPECT_EQ(header.devmajor.size(), 8u);
  EXPECT_EQ(header.devminor.size(), 8u);
  EXPECT_EQ(header.prefix.size(), 155u);
  EXPECT_EQ(header.padding.size(),
            12u); // Adjusted size to match the actual padding size
}

TEST(Tar, Dummy) {
  std::string filename{"altushka.tar"};
  {
    // Note: creator destructor is needed
    tar::Creator<std::ofstream> creator(filename);
    creator.addFile({"sqwoz.txt", "bab"});
  }
  fs::remove(filename);
}

TEST(Tar, Example) {

  // filename must contain absolute path indise tar
  // e.g. my/awesome/file.txt
  using FilenameAndData = std::pair<std::string, std::string>;
  std::vector<FilenameAndData> files{{"first/file.cpp", "#include <iostream>"},
                                     {"second/file.py", "import os"}};

  std::string inMemoryTar;
  {
    // Note: creator destructor is needed
    tar::Creator<std::ostringstream> creator(inMemoryTar);
    for (auto const &file : files) {
      creator.addFile({file.first, file.second, tar::FileType::RegularFile});
    }
  }

  ASSERT_FALSE(inMemoryTar.empty());
}
