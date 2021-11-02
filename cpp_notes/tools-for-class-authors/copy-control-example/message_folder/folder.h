#ifndef __FOLDER__
#define __FOLDER__
#include<set>
#include<iostream>
class Message;

class Folder
{
public:
    //explicit Folder();
    Folder()=default;
    ~Folder();
    Folder(const Folder &f);
    Folder& operator=(const Folder &f);
    void add_message(Message *message);
    void remove_message(Message *message);
private:
    std::set<Message *> messages_;
    void add_to_messages(const Folder &f);
    void remove_from_messages();

};

# endif