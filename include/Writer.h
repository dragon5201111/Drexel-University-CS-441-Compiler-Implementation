#pragma once
#include <string>

class Writer {
public:
    virtual ~Writer() = default;
    virtual void write(std::string message) = 0;
};

class ConsoleWriter : public Writer {
public:
    void write(std::string message) override;
};
