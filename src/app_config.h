#ifndef APP_CONFIG_H
#define APP_CONFIG_H

#include <filesystem>

struct AppConfig {
    std::filesystem::path asset_root;
};

#endif