#pragma once

#include <filesystem>
#include <string>

namespace engine {

    class Paths {
    public:
        static std::filesystem::path getExecutableDir();

        static std::string resolve(const std::string& relative_path);
    
    private:
        Paths();
    };

}
