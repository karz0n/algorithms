#ifndef DATA_HPP
#define DATA_HPP

#include <string>
#include <iostream>

struct Data {
    Data(const std::string& name, bool logging = false)
        : name{name}
        , logging{logging}
    {
        if (logging) {
            std::cout << "ctor: " << name << std::endl;
        }
    }

    Data(const Data& other)
        : name{other.name}
        , logging{other.logging}
    {
        if (logging) {
            std::cout << "ptor: " << name << std::endl;
        }
    }

    Data(Data&& other)
        : name{std::move(other.name)}
        , logging{other.logging}
    {
        if (logging) {
            std::cout << "mtor: " << name << std::endl;
        }
    }

    const Data& operator=(const Data& other)
    {
        if (this == &other) {
            return *this;
        }

        name = other.name;
        logging = other.logging;

        if (logging) {
            std::cout << "cper: " << name << std::endl;
        }

        return *this;
    }

    Data& operator==(Data&& other)
    {
        if (this == &other) {
            return *this;
        }

        name = std::move(other.name);
        logging = other.logging;

        if (logging) {
            std::cout << "mper: " << name << std::endl;
        }

        return *this;
    }

    ~Data()
    {
        if (logging) {
            if (name.empty()) {
                name = "<empty>";
            }
            std::cout << "dtor: " << name << std::endl;
        }
    }

    std::string name;
    bool logging;
};

#endif // DATA_HPP
