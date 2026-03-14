#ifndef CONFIG_MANAGER_HPP
#define CONFIG_MANAGER_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <nlohmann/json.hpp>

struct DbConfig {
    std::string name;
    std::string user;
    std::string password;
    std::string address;
    std::string port;
};

class ConfigManager {
private:
    nlohmann::json configData;
    bool isLoaded = false;

public:

    ConfigManager(const std::string& filePath) {
        std::ifstream file(filePath);
        if (file.is_open()) {
            try {
                file >> configData;
                isLoaded = true;
            }
            catch (const std::exception& e) {
                std::cerr << "JSON Parse Hatasi: " << e.what() << std::endl;
            }
        }
        else {
            std::cerr << "Config Dosyasi Acilamadi!" << std::endl;
        }
    }

    bool success() const { return isLoaded; }

    DbConfig getDatabaseConfig() {
        auto db = configData["database"];
        return {
            db.value("name", "default_db"),
            db.value("user", "postgres"),
            db.value("password", ""),
            db.value("address", "127.0.0.1"),
            std::to_string(db.value("port", 5432))
        };
    }

};

#endif