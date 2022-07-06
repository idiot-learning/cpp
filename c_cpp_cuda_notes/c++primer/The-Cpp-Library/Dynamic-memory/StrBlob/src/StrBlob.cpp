#include "StrBlob.h"

StrBlob::StrBlob() : data(std::make_shared<std::vector<std::string>>()) {}

//The constructor that takes an initializer_list passes its parameter to the corresponding vector constructor (§ 2.2.1, p. 43).
//That constructor initializes the vector’s elements by copying the values in the list
StrBlob::StrBlob(std::initializer_list<std::string> il) : data(std::make_shared<std::vector<std::string>>(il)) {}

void StrBlob::check(size_type i, const std::string &msg) const
{
    if (i >= data->size())
        throw std::out_of_range(msg);
}
std::string &StrBlob::front() const
{
    // if the vector is empty, check will throw
    check(0, "front on empty StrBlob");
    return data->front();
}
std::string &StrBlob::back() const
{
    check(0, "back on empty StrBlob");
    return data->back();
}
void StrBlob::pop_back()
{
    check(0, "pop_back on empty StrBlob");
    data->pop_back();
}
// this func is used for showing the content of data
void StrBlob::print(){
    std::vector<std::string> vec = *data;
    for (auto iter: vec)
    {
        std::cout << iter<< " ";
    }
    std::cout << std::endl;
}
StrBlobPtr StrBlob::begin() { return StrBlobPtr(*this); }
StrBlobPtr StrBlob::end()
{ return StrBlobPtr(*this, data->size()); }
int main()
{
    StrBlob b1;
    {
        StrBlob b2 = {"a", "an", "the"};
        b1 = b2;
        b2.push_back("about");
        std::cout << "b1 is: ";
        b1.print();
        std::cout << "b2 is: ";
        b2.print();
    }
    return 0;
}