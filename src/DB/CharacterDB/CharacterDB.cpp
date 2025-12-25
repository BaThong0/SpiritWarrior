#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class CharacterDB 
{
    public:
        explicit CharacterDB(const std::string& filePath)
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
                data["characters"] = json::array();
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
            return data["characters"];
        }

        json getById(int id) const 
        {
            for(auto& c : data["characters"])
            {
                if(c["id"] == id)
                    return c;
            }
            throw std::runtime_error("Character not found");
        }

        bool exist(int id) const 
        {
            for(auto& c : data["characters"])
            {
                if(c["id"] == id)
                {
                    return true;
                }
            }
            return false;
        }

        void addCharacter(const json& character)
        {
            if(!character.contains("id"))
            {
                throw std::runtime_error("Character missing id!");
            }
            int id = character["id"];
            if(exist(id))
            {
                throw std::runtime_error("CharacterID already exists!");
            }
            data["characters"].push_back(character);
            save();
        }

        void updateCharacter(int id, const json& updated) 
        {
        for (auto& c : data["characters"]) {
            if (c["id"] == id) {
                for (auto& [key, value] : updated.items())
                    c[key] = value;

                save();
                return;
            }
        }
        throw std::runtime_error("Character not found");
        }

        void removeCharacter(int id) 
        {
        auto& arr = data["characters"];
        for (auto it = arr.begin(); it != arr.end(); ++it) {
            if ((*it)["id"] == id) {
                arr.erase(it);
                save();
                return;
            }
        }
        throw std::runtime_error("Character not found");
        }

    private:
        std::string dbFile;
        json data;
};

int main() {
    CharacterDB db("characters.json");

    // Add character
    db.addCharacter({
        {"id", 3},
        {"name", "Archer"},
        {"image", "path"},
        {"health", 120},
        {"mana", 300},
        {"armor", 130},
        {"damage", 7} 
    
    });

    // Get
    auto c = db.getById(3);
    std::cout << c.dump(4) << std::endl;

    c = db.getById(1);
    std::cout << c.dump(2) << std::endl;

    c = db.getById(2);
    std::cout << c.dump(3) << std::endl;
    // Update
    db.updateCharacter(3, {
        {"hp", 180}
    });

    // Remove
    db.removeCharacter(1);
}
