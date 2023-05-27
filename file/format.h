//
// Created by Joseph Middleton on 10/05/2023.
//

#ifndef GARDEN_FORMAT_H

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../misc/types.h"
#include <cereal/types/unordered_map.hpp>
#include <cereal/types/string.hpp>
#include <cereal/archives/binary.hpp>


#define GARDEN_FORMAT_H

namespace garden {

    enum TYPES{
        EMPTY = 0,
        TEST = 1,
        HEADER = 2,
    };

    struct dataStruct{
        int type;
        std::string desc;

        template<class Archive>
        void serialize(Archive &ar){
            ar(type, desc);
        }
    };

    class fileFormat {


//        std::unordered_map<std::string, std::vector<u_char>> objects;


    public:
        // empty dataStruct for empty results
        dataStruct empty{
            EMPTY,
        };

        // test element to check the file decoded correctly
        dataStruct header{
            HEADER,
            "CHACHACHA"
        };



        std::unordered_map<std::string, dataStruct> containedData;

        fileFormat() = default;

        /*
         *  Inserts a pair of idName and datastruct with the associated type
         *
         */
        void addDirectField(std::string idName, std::string desc, int type){
            containedData.emplace(std::pair<std::string,dataStruct>(idName,{
                (int) type,
                std::move(desc),
            }));
        }

        /*
         *  Trys to return a reference to the Data in the map connected with the key idName.
         *  If no such key exists then the function returns empty datastruct with EMPTY type.
         */
        dataStruct& getField(std::string idName){
            auto item = containedData.find(idName);
            if(item == containedData.end()) {
                std::cout << "There is no object associated with this key" << std::endl;
                return empty;
            }
            return item->second;
        }

        template<class Archive>
        void serialize(Archive & ar) {
            ar( header, containedData );
        }
    };

} // garden

#endif //GARDEN_FORMAT_H
