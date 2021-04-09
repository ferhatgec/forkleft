// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//

#ifndef FORKLEFT_TOKENS_HPP
#define FORKLEFT_TOKENS_HPP

#include <string>
#include <vector>

#include "defs/forkleft_defs.hpp"


enum class ForkleftKeywords : const u8 {
        H1 = 0,
        H2    ,
        H3    ,
        H4    ,
        H5    ,
        H6    ,

        Italic       ,
        Bold         ,
        Blockquote   ,
        Sign         ,
        Label        ,
        Text         ,
        Code         ,
        Strikethrough,
        Link         ,
        Image        ,
        Title        ,

        Newline      ,
        Inline       ,
        HTML         ,

        Undefined
};

std::vector<std::string> keywords = {
        "h1",
        "h2",
        "h3",
        "h4",
        "h5",
        "h6",

        "italic"       ,
        "bold"         ,
        "blockquote"   ,
        "sign"         ,
        "label"        ,
        "text"         ,
        "code"         ,
        "strikethrough",
        "link"         ,
        "image"        ,
        "title"        ,

        "~newline~"    ,
        "~inline~"     ,
        "~html~"
};

std::vector<std::string> html_keywords {
        "h1",
        "h2",
        "h3",
        "h4",
        "h5",
        "h6",

        "em"        ,
        "strong"    ,

        "blockquote",

        "label"     , // sign
        "label"     , // label
        "label"     , // text

        "code"      ,
        "s"         ,
        "a"         ,
        "img"       ,
        "title"
};

const std::vector<std::string> signs = {
        "@copyright@" , // (C)
        "@registered@", // (R)
        "@trade-mark@", // (TM)
        "@section@"   , // (P)

        "@plus-minus@"  // +-
};

const std::vector<std::string> sign_implemented {
        "©", // (C)
        "®", // (R)
        "™", // (TM)
        "§", // (P)

        "±"  // +-
};

#endif // FORKLEFT_TOKENS_HPP
