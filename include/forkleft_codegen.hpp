// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//


#ifndef FORKLEFT_CODEGEN_HPP
#define FORKLEFT_CODEGEN_HPP

#include "forkleft_tokens.hpp"

class Forkleft_Codegen {
public:
    Forkleft_Codegen() = default;
    ~Forkleft_Codegen()= default;

    std::string InitType(std::string html, std::string data) noexcept {
        return "<" + html + ">" + data + "</" + html + ">";
    }

    void Init(ForkleftKeywords keyword,
              std::string& generated,
              std::string data,
              bool is_newline = false) noexcept {
        switch(keyword) {
            case ForkleftKeywords::H1        :
            case ForkleftKeywords::H2        :
            case ForkleftKeywords::H3        :
            case ForkleftKeywords::H4        :
            case ForkleftKeywords::H5        :
            case ForkleftKeywords::H6        :
            case ForkleftKeywords::Italic    :
            case ForkleftKeywords::Bold      :
            case ForkleftKeywords::Blockquote: {
                if(is_newline) {
                    generated.append(this->InitType("p", this->InitType(html_keywords[static_cast<u8>(keyword)], data)) + "\n");
                    break;
                }

                generated.append(this->InitType(html_keywords[static_cast<u8>(keyword)], data) + "\n");

                break;
            }
        }
    }
};

#endif // FORKLEFT_CODEGEN_HPP
