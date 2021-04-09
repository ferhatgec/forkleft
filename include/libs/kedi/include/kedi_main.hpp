// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//


#ifndef KEDI_MAIN_HPP
#define KEDI_MAIN_HPP

#include <iostream>
#include "kedi_tokens.hpp"
#include "kedi_tree.hpp"

typedef struct {
public:
    std::string file_name,
                file_data;
} kedi_init_t;

class Kedi {
    kedi_init_t data;
public:
    Kedi_Tree *Tree = new Kedi_Tree("init", {""});

    ~Kedi() {
        delete Tree;
    }


    void Read(std::string filename) noexcept {
        std::ifstream kedi_input(filename);

        Kedi_Tokenizer tokenizer;

        kedi_keywords_t init;

        for(std::string data; std::getline(kedi_input,data);) {
            init = tokenizer.Tokenize(data);

            if(data.length() == 0) continue;

            tokenizer.MatchTokens(init, Tree);
        }
    }

    void ReadStr(std::string str_data) noexcept {
        std::istringstream kedi_input(str_data);

        Kedi_Tokenizer   tokenizer;
        kedi_keywords_t  init;

        for(std::string _data; std::getline(kedi_input, _data);) {
            init = tokenizer.Tokenize(_data);

            if(_data.length() == 0) continue;

            tokenizer.MatchTokens(init, Tree);
        }
    }
};

#endif // KEDI_MAIN_HPP
