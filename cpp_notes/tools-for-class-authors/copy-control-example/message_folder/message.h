#ifndef __MESSAGE__
#define __MESSAGE__
#include "folder.h"
#include <set>
#include <string>
#include<iostream>
#include<memory>

class Message: public std::enable_shared_from_this<Message>
{
    friend class Folder;
    friend void swap(Message&, Message&);
public:
    explicit Message(const std::string &str = "") : contents_{str} {std::cout << "construct the message";};
    ~Message();
    Message(const Message &rhs);
    Message &operator=(const Message &message);
    // add/remove this Message from the specified Folder ’s set of messages
    void save(std::shared_ptr<Folder> );
    void remove(std::shared_ptr<Folder> );
    void add_folder(std::shared_ptr<Folder>f);
    void remove_folder(std::shared_ptr<Folder>f);
    void print_folders()
    {
        std::cout << "the message '" << contents_ <<"' is in "<< folders_.size()<< " folders"<< std::endl;
        for(auto const & folder: folders_)
        {
            std::cout << folder->GetName()<< std::endl;
        }
    }
    std::string get_content();
    std::shared_ptr<Message> get_shared_this() { return shared_from_this(); }

private:
    std::string contents_; // actual message text
    std::set<std::shared_ptr<Folder> > folders_;
    void add_to_folders(const Message &message);
    void remove_from_folders();
};

#endif