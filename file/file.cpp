//
// Created by Joseph Middleton on 10/05/2023.
//

#include <iomanip>
#include "file.h"

namespace garden {


    void file::printHex(std::span<char> vec, const std::string &name) {
        std::cout << name;
        for (char c : vec) {
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(static_cast<unsigned char>(c)) << ' ';
        }
        std::cout << std::dec;
    }



    void file::checkFileOperations() const{
        if(!_fileOperations) {
            std::cout << "Unable to perform File Operations" << std::endl;
            if(this->_hardExit){
                exit(1);
            }
        }
    }

    void file::open(std::string path, std::ios_base::openmode modes) {
        fileDescriptor.open(path, modes);
        if(fileDescriptor.is_open()){
            std::cout << "File: " << path << " is open." << std::endl;
            this->_fileOperations = true;
        }

    }

   void file::close(){
        fileDescriptor.close();
        _explictClose = true;
    }

    std::streamsize file::calculateSize(){
        this->fileDescriptor.ignore( std::numeric_limits<std::streamsize>::max() );
        std::streamsize tmp = this->fileDescriptor.gcount();
        this->fileDescriptor.clear();
        this->fileDescriptor.seekg(0, std::ios_base::beg);
        return tmp;
    }

    std::vector<char>& file::read(){
        checkFileOperations();
        // get full file size
        auto size = this->calculateSize();

        // reserve size
        this->contents.reserve(size);


        this->contents = std::vector<char>((std::istreambuf_iterator<char>(this->fileDescriptor)), std::istreambuf_iterator<char>());
        std::cout << "HEX: " << std::hex << this->contents.data() << std::endl;
        std::cout << "Size of the array: " << this->contents.size() << std::endl;

        return this->contents;

    }

    std::stringstream& file::readToStream(bool doRead){
        /*
         *      std::streambuf streambuffer;
         *      std::istream content_input;
         *      std::ostream content_output;
         *
         */
        if(doRead) {
            this->read();
        }
        printHex(this->contents, "READ MODE: ");
        this->content_input = new std::stringstream(std::string(this->contents.data(), this->contents.size()));
        return *this->content_input;

    }

    void file::write(const std::span<char> &data, bool appendMode){
        checkFileOperations();

        if(appendMode){
            // append mode so move file pointer to end
            this->fileDescriptor.seekg(std::ios::end);
        }
        printHex(data, "Write Data: ");
        std::cout << "Write Size: " << data.size() << std::endl;
        // write over file
        this->fileDescriptor.write(data.data(), data.size());


    }


} // garden