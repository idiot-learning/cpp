#ifndef __STRBLOB__
#define __STRBLOB__

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include "StrBlobPtr.h"


class StrBlob
{
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il);
    size_type size() const { return data->size(); }
    bool empty() const { return data->empty(); }
    // add and remove elements
    void push_back(const std::string &t) { data->push_back(t); }
    void pop_back();
    // element access
    std::string &front() const;
    std::string &back() const;
    // func used for printing the data
    void print();

private:
    friend class StrBlobPtr;
    StrBlobPtr begin(); // return StrBlobPtr to the first element
    StrBlobPtr end();
    std::shared_ptr<std::vector<std::string>> data;
    // throws msg if data[i] isn’t valid
    void check(size_type i, const std::string &msg) const;
    // other members as in § 12.1.1 (p. 456)

// and one past the last element
};

#endif