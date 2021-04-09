// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//


#ifndef FORKLEFT_CODEGEN_HPP
#define FORKLEFT_CODEGEN_HPP

#include <regex>
#include "forkleft_tokens.hpp"

class Forkleft_Codegen {
public:
    Forkleft_Codegen() = default;
    ~Forkleft_Codegen()= default;

    std::string InitType(std::string html, std::string data) noexcept {
        return "<" + html + ">" + data + "</" + html + ">";
    }

    std::string unwrap(const std::string& data) noexcept {
        std::smatch match;

        std::regex_search(data.begin(),
                          data.end()  ,
                          match    ,
                          std::regex("\'(.*)\'"));

        return match[1];
    }

    void Init(ForkleftKeywords keyword,
              std::string& generated,
              std::string data,
              std::string path,
              bool is_newline = false,
              bool is_inline  = false) noexcept {
        switch(keyword) {
            case ForkleftKeywords::H1           :
            case ForkleftKeywords::H2           :
            case ForkleftKeywords::H3           :
            case ForkleftKeywords::H4           :
            case ForkleftKeywords::H5           :
            case ForkleftKeywords::H6           :
            case ForkleftKeywords::Italic       :
            case ForkleftKeywords::Bold         :
            case ForkleftKeywords::Blockquote   :
            case ForkleftKeywords::Sign         :
            case ForkleftKeywords::Label        :
            case ForkleftKeywords::Text         :
            case ForkleftKeywords::Strikethrough:
            case ForkleftKeywords::Title        : {
                if(is_newline) {
                    generated.append(this->InitType("p", this->InitType(html_keywords[static_cast<u8>(keyword)], data)));
                    break;
                }

                generated.append(this->InitType(html_keywords[static_cast<u8>(keyword)], data));

                break;
            }


            case ForkleftKeywords::Code      : {
                if(is_inline) {
                    generated.append(this->InitType(html_keywords[static_cast<u8>(keyword)], data) + "\n");
                }

                break;
            }

            case ForkleftKeywords::Link: {
                generated.append("<"
                    + html_keywords[static_cast<u8>(ForkleftKeywords::Link)]
                    + " href=\""
                    + this->unwrap(path)
                    + "\">"
                    + this->unwrap(data)
                    + "</"
                    + html_keywords[static_cast<u8>(ForkleftKeywords::Link)]
                    + ">");

                break;
            }

            case ForkleftKeywords::Image: {
                generated.append("<"
                    + html_keywords[static_cast<u8>(ForkleftKeywords::Image)]
                    + " src=\""
                    + this->unwrap(path)
                    + "\" "
                    + "alt=\""
                    + this->unwrap(data)
                    + "\">");

                break;
            }

            case ForkleftKeywords::HTML: {
                generated.append(data);

                break;
            }
        }

        generated.push_back('\n');
    }
};

#endif // FORKLEFT_CODEGEN_HPP
