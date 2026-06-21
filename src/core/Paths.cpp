#include "engine/core/Paths.h"

#if defined(__linux__)
    #include <unistd.h>
#elif defined(__APPLE__)
    #include <mach-o/dyld.h>
#elif defined(_WIN32)
    #include <windows.h>
#endif

namespace engine {

    std::filesystem::path Paths::getExecutableDir() {
    #if defined(__linux__)
        char result[1024];
        ssize_t count = readlink("/proc/self/exe", result, sizeof(result));
        std::filesystem::path exePath(std::string(result, (count > 0) ? count : 0));

    #elif defined(__APPLE__)
        char result[1024];
        uint32_t size = sizeof(result);
        _NSGetExecutablePath(result, &size);
        std::filesystem::path exePath(result);

    #elif defined(_WIN32)
        wchar_t result[MAX_PATH];
        GetModuleFileNameW(NULL, result, MAX_PATH);
        std::filesystem::path exePath(result);

    #endif
        return exePath.parent_path();
    }

    std::string Paths::resolve(const std::string& relative_path) {
        return (getExecutableDir() / relative_path).string();
    }

}
