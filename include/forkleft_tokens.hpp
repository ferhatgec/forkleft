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

        Italic    ,
        Bold      ,
        Blockquote,
        Code      ,
        Strikethrough,
        Link      ,
        Image     ,

        Newline   ,
        Inline    ,
        Undefined
};

std::vector<std::string> keywords = {
        "h1",
        "h2",
        "h3",
        "h4",
        "h5",
        "h6",

        "italic",
        "bold",
        "blockquote",
        "code",
        "strikethrough",
        "link",
        "image",

        "~newline~",
        "~inline~"
};

std::vector<std::string> html_keywords {
        "h1",
        "h2",
        "h3",
        "h4",
        "h5",
        "h6",

        "em",
        "strong",

        "blockquote",
        "code",
        "s",
        "a",
        "img"
};

#endif // FORKLEFT_TOKENS_HPP
