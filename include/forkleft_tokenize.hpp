// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//

#ifndef FORKLEFT_TOKENIZE_HPP
#define FORKLEFT_TOKENIZE_HPP

#include <iostream>
#include <vector>
#include <sstream>

#include "forkleft_parser.hpp"

#include "defs/forkleft_defs.hpp"

class Forkleft_Tokenize {
    std::vector<std::string> tokens = {};

    Forkleft_Parser parser;
public:
    Forkleft_Tokenize() = default;
    ~Forkleft_Tokenize()= default;

    std::string Get() noexcept {
        return parser.Get();
    }

    void Init(std::string data) noexcept {
        std::istringstream temporary_stream(data);

        bool is_data = false;

        for(std::string temporary_line; std::getline(temporary_stream, temporary_line); ) {
            std::istringstream temporary_line_stream(temporary_line);

            for(std::string temporary; temporary_line_stream >> temporary;) {
                if(temporary.empty()) break;

                if(temporary.length() >= 2 && !is_data) {
                    // Supported comment blocks:
                    //  ~= Hi
                    //  =~ Hi
                    //
                    if((temporary.front() == '~' || temporary.front() == '=')
                        && (temporary[1] == '=' || temporary[1] == '~')) {
                        break;
                    }
                }

                if(temporary.front() == '\'') is_data = true;

                if(is_data) {
                    if(temporary.back() == '\'') {
                        this->tokens.push_back(temporary);
                        is_data = false;
                    } else {
                        this->tokens.push_back(temporary + " ");
                    }

                    continue;
                }

                this->tokens.push_back(temporary);
            }

            parser.Init(this->tokens);

            parser.Parse(temporary_line);

            this->tokens.clear();
        }
    }
};

#endif // FORKLEFT_TOKENIZE_HPP
