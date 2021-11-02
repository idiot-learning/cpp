#ifndef __MESSAGE__
#define __MESSAGE__
#include "folder.h"
#include <set>
#include <string>
#include<iostream>
class Message
{
    friend class Folder;
    friend void swap(Message&, Message&);
public:
    explicit Message(const std::string &str = "") : contents_{str} {};
    ~Message();
    Message(const Message &rhs);
    Message &operator=(const Message &message);
    // add/remove this Message from the specified Folder ’s set of messages
    void save(Folder &);
    void remove(Folder &);
    void add_folder(Folder *f);
    void remove_folder(Folder *f);
    void print_folders()
    {
        std::cout << "the message" << contents_ <<" is in "<< folders_.size()<< "folders"<< std::endl;
    }
    std::string get_content();
private:
    std::string contents_; // actual message text
    std::set<Folder *> folders_;
    void add_to_folders(const Message &message);
    void remove_from_folders();
};

#endif