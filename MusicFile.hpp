#pragma once
#include "File.hpp"

#include <string>

class MusicFile : public File
{
    double trackLength_{};

   public:
    MusicFile() = default;
    MusicFile(const std::string& name, double length):File(name), trackLength_(length){};
    int getSize() const override { return trackLength_ * 50; }
};
