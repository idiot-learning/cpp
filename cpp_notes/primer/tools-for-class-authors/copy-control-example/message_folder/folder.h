#ifndef __FOLDER__
#define __FOLDER__
#include<set>
#include<iostream>
#include<memory>
class Message;

class Folder : public std::enable_shared_from_this<Folder>
{
public:
    //explicit Folder();
    explicit Folder(const std::string& folder_name_ );
    ~Folder();
    Folder(const Folder &f);
    Folder& operator=(const Folder &f);
    void add_message(std::shared_ptr<Message> message);
    void remove_message(std::shared_ptr<Message> message);
    std::string GetName();

    // miscellaneous
    std::shared_ptr<Folder> get_shared_this() { return shared_from_this(); }
    
private:
    std::set<std::shared_ptr<Message> > messages_;
    std::string folder_name;
    void add_to_messages(const Folder &f);
    void remove_from_messages();

};

# endif