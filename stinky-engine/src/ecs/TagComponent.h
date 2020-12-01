//
// Created by christian on 04/11/2020.
//

#pragma once

#include <string>

class TagComponent {
public:
    explicit TagComponent() = default;
    explicit TagComponent(std::string name) : name(std::move(name)) {}
    ~TagComponent() = default;

    std::string name;
};