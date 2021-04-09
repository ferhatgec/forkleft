// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//

#ifndef KEDI_HELPERS_HPP
#define KEDI_HELPERS_HPP

#include <iostream>
#include "kedi_tokens.hpp"

class Kedi_Helpers {
public:
    char GetInitializer(std::string &data) {
        return (data.length() >= 1) ? data[0] : ' ';
    }

    std::tuple<std::string, std::string> ExtractVar(std::string variable) noexcept {
        std::string temporary_variable_name, temporary_variable_data;

        unsigned i = 0;
        for(; variable[i] != ':'; i++) {
            temporary_variable_name.push_back(variable[i]);
        }

        for(i = i + 1; variable[i] != '\0'; i++) {
            temporary_variable_data.push_back(variable[i]);
        }

        return std::make_tuple(temporary_variable_name, temporary_variable_data);
    }
};

#endif // KEDI_HELPERS_HPP
