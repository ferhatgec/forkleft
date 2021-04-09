// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//

#ifndef FORKLEFT_PARSER_HPP
#define FORKLEFT_PARSER_HPP

#include <algorithm>
#include <tuple>

#include "forkleft_codegen.hpp"
#include "forkleft_tokens.hpp"

#include "libs/kedi/include/kedi_main.hpp"

class Forkleft_Parser {
    std::vector<std::string> tokens;

    bool is_found       = false;

    // Initializer
    bool is_newline     = false;
    bool is_inline      = false;
    bool is_kedi        = false;
    bool is_html        = false;

    bool is_setter      = false;
    bool is_data        = false;

    bool is_end_of_html_data = false;

    std::string data        ;
    std::string keyword_data;
    std::string generated   ;

    std::string kedi_data   ;
    std::string kedi_path   ;

    std::string html_data   ;

    ForkleftKeywords current_token;
    Forkleft_Codegen cg           ;
public:
    Forkleft_Parser() = default;
    ~Forkleft_Parser()= default;

    void Init(std::vector<std::string>& data) noexcept {
        this->tokens = data;
    }

    std::string& Get() noexcept {
        return this->generated;
    }

    void left_trim(std::string& data) noexcept {
        data.erase(
                data.begin(),
                std::find_if(data.begin(),
                             data.end(),
                             [](unsigned char ch) { return !std::isspace(ch);}
                             )
        );
    }

    void Parse(const std::string& line) noexcept {
        for(auto& data : this->tokens) {
            if(this->is_found) {
                if(this->is_html) {
                    // code ~html~ := -> '
                    //
                    //
                    //
                    // ' <-
                    if(data == ":=" || data == "->") {
                        continue;
                    }

                    if(data == "'") {
                        if(!this->is_end_of_html_data) {
                            this->is_end_of_html_data = true;
                        }

                        continue;
                    }

                    if(data == "<-") {
                        this->is_end_of_html_data = this->is_html = false;

                        this->left_trim(this->html_data);

                        cg.Init(ForkleftKeywords::HTML,
                                this->generated,
                                this->html_data,
                                "",
                                this->is_newline,
                                this->is_inline);

                        this->html_data.erase();

                        continue;
                    }


                    this->html_data.append(line);

                    break;
                }

                if(this->is_kedi) {
                    // keyword @= ->
                    //  [data
                    //      =link '....'
                    //      =name '....'
                    //  ]
                    // <-
                    if(data == "->") {
                        break;
                    }

                    if(data == "<-") {
                        this->is_kedi = false;

                        Kedi tree;

                        tree.ReadStr(this->kedi_data);

                        this->data = std::get<1>(tree.Tree->Extract("data", "text"));
                        this->kedi_path = std::get<1>(tree.Tree->Extract("data", "path"));

                        cg.Init(this->current_token,
                                this->generated,
                                this->data,
                                this->kedi_path,
                                this->is_newline,
                                this->is_inline);

                        this->is_found = this->is_data = false;

                        this->data     .erase();
                        this->kedi_path.erase();
                        this->kedi_data.erase();

                        break;
                    }

                    kedi_data.append(data + " ");

                    if(data.back() == '\'' || data.front() == '[') {
                        kedi_data.push_back('\n');
                    }

                    continue;
                }

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
                                        "",
                                        this->is_newline,
                                        this->is_inline);

                                this->keyword_data.clear();
                                this->data.clear();

                                break;
                            }
                        }
                    }

                    // keyword := 'lol'
                    if(data.front() == '\'') {
                        this->is_data = true;

                        char check = ' ';

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
                    this->is_newline= true;

                    continue;
                }

                if(data == keywords[static_cast<u8>(ForkleftKeywords::Inline)]) {
                    this->is_inline = true;

                    continue;
                }

                if(data == keywords[static_cast<u8>(ForkleftKeywords::HTML)]) {
                    this->is_html   = true;

                    continue;
                }

                if(data == ":=") {
                    this->is_setter = true;

                    continue;
                }

                if(data == "@=") {
                    this->is_kedi = true;

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
