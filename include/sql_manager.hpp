#ifndef SQL_MANAGER_HPP
#define SQL_MANAGER_HPP

#include <iostream>
#include <string>
#include <sstream>
#include "db_manager.hpp"

class SqlManager {
private:
    DbManager& db;

public:
    SqlManager(DbManager& dbInstance) : db(dbInstance) {
        init();
    }

    void init() {
        std::string urunTableSql =  "CREATE TABLE IF NOT EXISTS urunler ("
                                    "urunKodu char(10) primary key,"
                                    "urunAdi varchar(50) not null,"
                                    "urunFiyat NUMERIC(12,2) not null,"
                                    "urunAdet INT DEFAULT 1)";

        db.executeQuery(urunTableSql);

        std::string subelerSql =    "CREATE TABLE IF NOT EXISTS subeler ("
                                    "subeId SERIAL primary key,"
                                    "subeAd varchar(50) not null)";

        db.executeQuery(subelerSql);

        std::string departmanlarSql =   "CREATE TABLE IF NOT EXISTS departmanlar ("
                                        "departmanId SERIAL primary key,"
                                        "departmanAd varchar(50) not null)";

        db.executeQuery(departmanlarSql);

        std::string personelTableSql =  "CREATE TABLE IF NOT EXISTS personel ("
                                        "personelNo INT primary key,"
                                        "personelAd varchar(50) not null,"
                                        "personelSoyad varchar(20) not null,"
                                        "personelDepartmanId INT,"
                                        "personelSubeId INT,"
                                        "FOREIGN KEY (personelDepartmanId) REFERENCES departmanlar(departmanId),"
                                        "FOREIGN KEY (personelSubeId) REFERENCES subeler(subeId))";

        db.executeQuery(personelTableSql);
    }

    bool subeEkle(std::string subeAdi) {
        std::string sql = "INSERT INTO subeler(subead) VALUES ($1);";
        db.executeParams(sql, subeAdi);
        return true;
    }

    bool departmanEkle(std::string departmanAdi) {
        std::string sql = "INSERT INTO departmanlar(departmanad) VALUES ($1);";
        db.executeParams(sql, departmanAdi);
        return true;
    }

};

#endif