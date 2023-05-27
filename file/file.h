//
// Created by Joseph Middleton on 10/05/2023.
//

#ifndef GARDEN_FILE_H
#include <iostream>
#include <fstream>
#include <vector>
#include <span>
#include <limits>
#include <sstream>
#include "../misc/types.h"
#define GARDEN_FILE_H



namespace garden {

    class file {

        std::fstream fileDescriptor;

        // contents vector
        std::vector<char> contents;
        std::stringstream *content_input;

        bool _explictClose = false;
        bool _fileOperations = false;
        bool _hardExit = false;



        ~file(){
            if(!_explictClose){
                fileDescriptor.close();
            }

        }

        inline void checkFileOperations() const;

    public:

        static void printHex(std::span<char>, const std::string &name);
        file() = default;
        void open(std::string path, std::ios_base::openmode);
        std::streamsize calculateSize();
        void close();
        std::vector<char>& read();
        void write(const std::span<char> &data, bool appendMode);
        std::stringstream& readToStream(bool doRead = false);
    };

} // garden

#endif //GARDEN_FILE_H
