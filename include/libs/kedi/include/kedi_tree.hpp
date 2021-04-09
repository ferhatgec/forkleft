// MIT License
//
// Copyright (c) 2021 Ferhat Geçdoğan All Rights Reserved.
// Distributed under the terms of the MIT License.
//
//

#ifndef KEDI_TREE_HPP
#define KEDI_TREE_HPP

#include <iostream>
#include <utility>
#include <bits/stdc++.h>
#include <tuple>

#include "kedi_helpers.hpp"

/* Kedi (Kedi Experimental Data Interface) tree structure
 *
 * In Kedi:
 *  Left must be variable list.
 *  Right must be category.
 *
 *       category : node_name "init"
 *      /     \
 * variable    category : node_name "project"
 *  *             /  \
 *  *       variable  category...
 *          *         /       \
 *          *        /         category...
 *                variable...
 *  *
 *  *
 */

class Kedi_Tree {
private:
    std::string node_name = "";

    // In Kedi, left must be variable list.
    std::vector<std::string> left;

    // In Kedi, right must be child category.
    Kedi_Tree* right= NULL;
public:
    Kedi_Helpers helper;

    // Initialize
    Kedi_Tree(std::string node_name, std::vector<std::string> variables) {
        this->node_name = node_name;
        this->left = variables;
        this->right= NULL;
    }

    ~Kedi_Tree() {
        delete right;
    }

    void Init(std::string node_name, std::vector<std::string> variables) {
        this->node_name = node_name;
        this->left = variables;
        this->right= NULL;
    }

    void InsertVar(std::string node_name, std::string name, std::string data) {
        if(this->node_name == node_name) {
            this->left.push_back(name + ":" + data);
        }
        else {
            if(this->right == NULL) {
                this->right = new Kedi_Tree(node_name, {name + ":" + data});
            }
            else {
                this->right->InsertVar(node_name, name, data);
            }
        }
    }

    void InsertCategory(std::string node_name, std::vector<std::string> variables) {
        if(this->right == NULL) {
            this->right = new Kedi_Tree(node_name, variables);

            this->right->node_name = node_name;
            this->right->left = variables;
            this->right->right = NULL;
        }
        else {
            this->right->InsertCategory(node_name, variables);
        }
    }

    // It's experimental, work-in-progress.
    void Tree() {
        if(this->left.size() >= 1) {
            for(unsigned i = 0; i < this->left.size(); i++)
                std::cout << "Left : " << this->left[i] << "\n";
        }

        if(this->right->left.size() >= 1) {
            for(unsigned i =0; i < this->right->left.size(); i++)
                std::cout << "Right (1) : " << this->right->left[i] << "\n";

            if(this->right->right->left.size() >= 1) {
                for (unsigned i = 0; i < this->right->right->left.size(); i++)
                    std::cout << "Right (2) : " << this->right->right->left[i] << "\n";
            }
        }
    }

    std::vector<std::string> GetVariable(std::string node_name) {
        if(this->node_name == node_name) {
            return this->left;
        }
        else {
            return (this->right)->GetVariable(node_name);
        }
    }

    std::tuple<std::string, std::string> Extract(std::string node_name, std::string variable_name) {
        if(this->node_name == node_name) {
            auto vect = GetVariable(node_name);

            // Range-based iterator
            for(auto& iter : vect) {
                if(iter.length() > 3) {
                    for(auto data = helper.ExtractVar(iter); std::get<0>(data) == variable_name;) {
                        return data;
                    }
                }
            }
        }
        else {
            return (this->right)->Extract(node_name, variable_name);
        }

        // Not found.
        return std::make_tuple("", "");
    }
};

#endif // KEDI_TREE_HPP
