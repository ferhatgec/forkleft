#include "include/forkleft_tokenize.hpp"
#include <fstream>

int main() noexcept {
    std::ifstream read("test.forkleft");

    std::string forkleft_data;

    for(std::string temp; std::getline(read, temp);
        forkleft_data.append(temp + "\n"));

    read.close();

    Forkleft_Tokenize tokenize;

    tokenize.Init(forkleft_data);


    std::ofstream data("test.html", std::ios::trunc);

    data << tokenize.Get();

    data.close();
}