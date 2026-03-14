#ifndef DB_MANAGER_HPP
#define DB_MANAGER_HPP

#include <iostream>
#include <string>
#include <pqxx/pqxx>
#include <sstream>

#include "config_manager.hpp"

class DbManager {

private:
    std::string dbNamee;
    std::string dbPath;
    pqxx::connection* C = nullptr;

public:

    DbManager(const DbConfig& config) {
    std::stringstream ss;
    ss << "dbname=" << config.name 
       << " user=" << config.user 
       << " password=" << config.password 
       << " hostaddr=" << config.address 
       << " port=" << config.port;
    dbPath = ss.str();
    dbNamee = config.name;
}

    bool connect() {

        try {

            if (C == nullptr || !C->is_open()) {
                C = new pqxx::connection(dbPath);
                std::cout << "INFO: Veritabanina Basariyla Baglanildi: " << dbNamee << std::endl;
            }
            return true;
            
        }
        catch (const std::exception& e) {
            std::cerr << "ERROR: " << e.what() << std::endl;
            return false;
        }

    }

    pqxx::result executeQuery(std::string sql) {
        pqxx::work W(*C);
        pqxx::result R = W.exec(sql);
        W.commit();
        return R;
    }

    pqxx::result executeParams(std::string sql, std::string params) {
        pqxx::work W(*C);
        pqxx::result R = W.exec_params(sql, params);
        W.commit();
        return R;
    }

    void close() {
        try
        {
            if (C != nullptr) {
                if (C->is_open()) {
                    C->disconnect();
                }
                delete C;
                C = nullptr;
                std::cout << "Baglanti Kapatildi!" << std::endl;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "ERROR:" << e.what() << std::endl;
        }
        
    }

    ~DbManager() {
        close();
    }

};

#endif