// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//

#ifndef KEDI_TOKENS_HPP
#define KEDI_TOKENS_HPP

#include <iostream>
#include <vector>

#include "kedi_tree.hpp"
#include "kedi_main.hpp"

enum KediTokens {
    KediGlobal    = '!',
    KediTree      = '[',
    KediTreeEnd   = ']',
    KediObject    = '=',
    KediObjectData='\'',

    KediGlobalEnv = '@',

    KediUndefined = '?'
};

typedef struct {
public:
    std::vector<std::string> tokens;

    std::string last_line = "";
} kedi_keywords_t;

typedef struct {
    std::vector<std::string> envs;
} kedi_globalenv_t;

class Kedi_Tokenizer {
public:
    kedi_keywords_t  keys;
    kedi_globalenv_t envs;

    bool is_global       = false;
    std::string last_key = "";

    void ltrim(std::string &data) {
        data.erase(data.begin(), std::find_if(data.begin(), data.end(),
                                              [](unsigned char ch) {
                                                  return !std::isspace(ch);
                                              }
        ));
    }

    kedi_keywords_t Tokenize(std::string data) noexcept {
        std::string append;
        std::vector<std::string> temporary_vector;

        ltrim(data);

        for(std::istringstream kedi_stream(data); kedi_stream >> append;){
            temporary_vector.push_back(append);
        }

        return kedi_keywords_t{temporary_vector, ""};
    }

    void MatchTokens(kedi_keywords_t &init, Kedi_Tree *&tree) noexcept {
        switch(init.tokens[0][0]) {
            case '=': {
                // Check first and last character of string
                if((init.tokens[1].front() != KediObjectData
                   || init.tokens.back()[init.tokens.size() - 1] == KediObjectData)
                   && init.tokens[1].front() != '$') {
                    break;
                }

                std::string data = "";


                if(init.tokens[1].front() == '$') {
                    std::string env_data = init.tokens[1].erase(0, 1);

                    for(auto& iter : envs.envs) {
                        if(iter == env_data) {
                            data.append(getenv(env_data.c_str()));
                        }
                    }
                }
                else if(1 >= init.tokens.size()) {
                    data.append(init.tokens[2]);
                }
                else {
                    for(int i = 1; i < init.tokens.size(); i++) {
                        data.append(init.tokens[i]);

                        data.append(1, ' ');
                    }
                }

                tree->InsertVar(last_key, init.tokens[0].erase(0, 1), data);

                break;
            }

            case '[': {
                last_key = init.tokens[0].erase(0, 1);

                tree->InsertCategory(last_key, {""});

                break;
            }

            case '@': {
                if(is_global) {
                    is_global = false;
                    break;
                }

                std::string type = init.tokens[0].erase(0, 1);

                if(type == "globalenv") {
                    is_global = true;
                }

                break;
            }

            case '$': {
                std::string env = init.tokens[0].erase(0, 1);

                if(env.length() >= 1) {
                    envs.envs.push_back(env);
                }

                break;
            }
        }
    }
};


#endif // KEDI_TOKENS_HPP