#ifndef TEST_EXCEPTION_H
#define TEST_EXCEPTION_H

#include <string>

class Exception : public std::exception {

private:

    std::string message;

public:

    explicit Exception(std::string  message);

    const char* what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_USE_NOEXCEPT override;

};


#endif //TEST_EXCEPTION_H
