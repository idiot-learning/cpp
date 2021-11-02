#include "message.h"

void Message::save(Folder &f)
{
    folders_.insert(&f);
    f.add_message(this);
}

void Message::remove(Folder &f)
{
    folders_.erase(&f);
    f.remove_message(this);
}

void Message::remove_folder(Folder *f)
{
    folders_.erase(f);
}

void Message::add_folder(Folder *f)
{
    folders_.erase(f);
}
void Message::add_to_folders(const Message &message)
{
    for (auto folder : message.folders_)
    {
        folder->add_message(this);
    }
}

Message::Message(const Message &rhs) : contents_{rhs.contents_}, folders_{rhs.folders_}
{
    add_to_folders(rhs);
}

void Message::remove_from_folders()
{
    for (auto folder : folders_)
    {
        std::cout << "called the remove_message"<< std::endl;
        folder->remove_message(this);
    }
    folders_.clear();
}

Message::~Message()
{
    std::cout << "inside the destructor" << std::endl;
    remove_from_folders();
}

Message& Message::operator=(const Message &message)
{
    std::cout << "inside assignment operator" << std::endl;
    remove_from_folders();
    folders_ = message.folders_;
    contents_ = message.contents_;
    add_to_folders(message);
    return *this;
}
std::string Message::get_content()
{
    return contents_;
}
void swap(Message &lhs, Message &rhs)
{
    using std::swap;
    for (auto f : lhs.folders_)
        f->remove_message(&lhs);
    for (auto f : rhs.folders_)
        f->remove_message(&rhs);
    // swap contents and folder pointers
    swap(lhs.contents_, rhs.contents_);
    swap(lhs.folders_, rhs.folders_);
    for(auto f : lhs.folders_)
        f->add_message(&lhs);
    for(auto f: rhs.folders_)
        f->add_message(&rhs);
}