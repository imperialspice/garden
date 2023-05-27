#include <iostream>
#include "botan_all.h"
#include "file/file.h"
#include "file/format.h"
#include <cereal/archives/binary.hpp>



int main() {

//    FILE->open("helloworld.txt", std::ios::binary|std::ios::out|std::ios::in|std::ios::trunc);
//    std::string SayHello = "Hello World";
////    std::vector<char> stringV(SayHello.begin(), SayHello.end());
//
//    std::vector<char> password(256);
//    std::cin.getline(password.data(), 256);
//
//    auto passwd = Botan::PasswordHashFamily::create_or_throw("Argon2i");
//    auto pwdhash = passwd->tune(32, std::chrono::milliseconds(10), 64);
//
//    std::array<uint8_t, 32> salt{};
//    Botan::system_rng().randomize(salt);
//    std::array<uint8_t, 32> key{};
//    pwdhash->hash(key, SayHello, salt);
//
//    std::cout << "Password String: " << pwdhash->to_string() << std::endl;
//
//    std::cout << Botan::hex_encode(key) << std::endl;
//    FILE->write(key, false);
//
//    FILE->close();



    auto FILE = new garden::file();
    auto FILEOUT = new garden::file();
    std::stringstream ss;

    {
        cereal::BinaryOutputArchive writeArchive(ss);
        //std::shared_ptr<garden::fileFormat> file = std::make_shared<garden::fileFormat>();
        garden::fileFormat file{};
        file.addDirectField("test", "this is a test field", garden::TEST);
        writeArchive(file);
    }
    std::vector<char> file;
    std::copy(std::istreambuf_iterator<char>(ss), std::istreambuf_iterator<char>(), std::back_inserter(file));
    FILE->open("binarytest.txt", std::ios::binary|std::ios::out|std::ios::in|std::ios::trunc);


    FILE->write(file, false);
    FILE->close();

    FILEOUT->open("binarytest.txt", std::ios::binary|std::ios::in);
    std::vector<char> format;
    FILEOUT->read();

    garden::fileFormat input;
    {
        cereal::BinaryInputArchive readArchive(FILEOUT->readToStream());
        readArchive(input);
    }

    auto test = input.getField("test");
    std::cout << test.desc << std::endl;

}
