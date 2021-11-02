#include<memory>
#include<vector>
#include<string>
#include"StrBlobPtr.h"
class StrBlob
{
public:
    typedef std::vector<std::string>::size_type size_type;
    StrBlob();
    StrBlob(std::initializer_list<std::string> il); 
    size_type size() {return data->size();}
    bool empty()const{return data->empty();}
    void pop_back();
    void push_back(const std::string & str){data->push_back(str);}
    std::string front();
    std::string back();

private:
    friend class StrBlobPtr;
    StrBlobPtr begin();
    StrBlobPtr end();
    std::shared_ptr<std::vector<std::string>> data;

};