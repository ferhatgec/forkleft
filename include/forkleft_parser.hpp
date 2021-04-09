// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//

#ifndef FORKLEFT_PARSER_HPP
#define FORKLEFT_PARSER_HPP

#include "forkleft_codegen.hpp"

#include "forkleft_tokens.hpp"

class Forkleft_Parser {
    std::vector<std::string> tokens;

    bool is_found       = false;

    // Initializer
    bool is_newline     = false;

    bool is_setter      = false;
    bool is_data        = false;

    std::string data;
    std::string keyword_data;
    std::string generated;

    ForkleftKeywords current_token;
    Forkleft_Codegen cg;
public:
    Forkleft_Parser() = default;
    ~Forkleft_Parser()= default;

    void Init(std::vector<std::string>& data) noexcept {
        this->tokens = data;
    }

    std::string& Get() noexcept {
        return this->generated;
    }

    void Parse() noexcept {
        for(auto& data : this->tokens) {
            if(this->is_found) {
                if(this->is_setter) {
                    if(data.empty()) { // keyword := (newline)
                        this->is_found = this->is_setter = false;
                        continue;
                    }

                    if(is_data) {
                        for(char& ch : data) {
                            if(ch != '\'') {
                                this->keyword_data.push_back(ch);
                            }
                            else {
                                this->is_data = this->is_setter = this->is_found = false;

                                cg.Init(this->current_token,
                                        this->generated,
                                        this->keyword_data,
                                        this->is_newline);

                                std::cout << this->data << " : " << this->keyword_data << '\n';
                                this->keyword_data.clear();
                                this->data.clear();

                                break;
                            }
                        }
                    }

                    // keyword := 'lol'
                    if(data.front() == '\'') {
                        this->is_data = true;

                        char check;

                        for(char& ch : data.erase(0, 1)) {
                            if(check == '\\' && ch == '\'') {
                                this->keyword_data.push_back('\'');
                                check = ' ';

                                continue;
                            }

                            if(ch == '\\') { check = ch; continue; }

                            this->keyword_data.push_back(ch);
                        }

                        continue;
                    }
                }

                if(data == keywords[static_cast<u8>(ForkleftKeywords::Newline)]) {
                    this->is_newline = true;

                    continue;
                }

                if(data == ":=") {
                    this->is_setter = true;

                    continue;
                }
            }

            auto check = this->is_keyword(data);

            if(check != ForkleftKeywords::Undefined) {
                this->is_found = true;
                this->data = data;
                this->current_token = check;

                continue;
            }
        }
    }

    ForkleftKeywords is_keyword(const std::string& data) noexcept {
        unsigned i = 0;

        for(auto& keyword : keywords) {
            if(keyword == data) {
                return static_cast<ForkleftKeywords>(i);
            }

            ++i;
        }

        return ForkleftKeywords::Undefined;
    }
};

#endif // FORKLEFT_PARSER_HPP
