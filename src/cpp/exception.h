#pragma once
#include <string>

class Exception : public std::exception {

private:

    std::string message;

public:

    explicit Exception(std::string  message);

    const char* what() const noexcept override;

};
