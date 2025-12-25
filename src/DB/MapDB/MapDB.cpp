#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class MapDB 
{
    public:
        explicit MapDB(const std::string& filePath)
            : dbFile(filePath)
        {
            load();
        }
        void load()
        {
            std::ifstream in(dbFile);
            if(!in.is_open())
            {
                data = json::object();
                data["maps"] = json::array();
                save();
                return;
            }
            in >> data;
        }
        void save()
        {
            std::string tmpFile = dbFile + ".tmp";
            std::ofstream out(tmpFile);
            if(!out.is_open())
                throw std::runtime_error("Cannot open temp DB file!");
            out << data.dump(4);
            out.close();

            std::remove(dbFile.c_str());
            std::rename(tmpFile.c_str(), dbFile.c_str());
        }

        const json& getAll() const
        {
            return data["maps"];
        }

        json getById(int id) const 
        {
            for(auto& c : data["maps"])
            {
                if(c["id"] == id)
                    return c;
            }
            throw std::runtime_error("Map not found");
        }

        bool exist(int id) const 
        {
            for(auto& c : data["maps"])
            {
                if(c["id"] == id)
                {
                    return true;
                }
            }
            return false;
        }

        void addMap(const json& map)
        {
            if(!map.contains("id"))
            {
                throw std::runtime_error("Map missing id!");
            }
            int id = map["id"];
            if(exist(id))
            {
                throw std::runtime_error("MapID already exists!");
            }
            data["maps"].push_back(map);
            save();
        }

        void updateMap(int id, const json& updated) 
        {
        for (auto& c : data["maps"]) {
            if (c["id"] == id) {
                for (auto& [key, value] : updated.items())
                    c[key] = value;

                save();
                return;
            }
        }
        throw std::runtime_error("Map not found");
        }

        void removeMap(int id) 
        {
        auto& arr = data["maps"];
        for (auto it = arr.begin(); it != arr.end(); ++it) {
            if ((*it)["id"] == id) {
                arr.erase(it);
                save();
                return;
            }
        }
        throw std::runtime_error("Map not found");
        }

    private:
        std::string dbFile;
        json data;
};

int main() {
    MapDB db("maps.json");

    // Add Map
    db.addMap({
        {"id", 3},
        {"name", "WinterLand"},
        {"image", "path"},
    });

    // Get
    auto c = db.getById(3);
    std::cout << c.dump(4) << std::endl;

    c = db.getById(1);
    std::cout << c.dump(2) << std::endl;

    c = db.getById(2);
    std::cout << c.dump(3) << std::endl;

    // Remove
    db.removeMap(1);
}
