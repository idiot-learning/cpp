#include "message.h"

void Message::save(std::shared_ptr<Folder> f)
{
    folders_.insert(f);
    f->add_message(shared_from_this());
}

void Message::remove(std::shared_ptr<Folder> f)
{
    folders_.erase(f);
    f->remove_message(shared_from_this());
}

void Message::remove_folder(std::shared_ptr<Folder>  f)
{
    folders_.erase(f);
}

void Message::add_folder(std::shared_ptr<Folder>  f)
{
    folders_.insert(f);
}

void Message::add_to_folders(const Message &message)
{
    for (auto folder : message.folders_)
    {
        folder->add_message(shared_from_this());
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
        folder->remove_message(shared_from_this());
    }
    folders_.clear();
}

Message::~Message()
{
    std::cout << "inside the destructor of Message" << std::endl;
    remove_from_folders();
}

Message& Message::operator=(const Message &message)
{
    std::cout << "inside assignment operator of Message" << std::endl;
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
        f->remove_message(std::make_shared<Message>(lhs));
    for (auto f : rhs.folders_)
        f->remove_message(std::make_shared<Message>(rhs));
    // swap contents and folder pointers
    swap(lhs.contents_, rhs.contents_);
    swap(lhs.folders_, rhs.folders_);
    for(auto f : lhs.folders_)
        f->add_message(std::make_shared<Message>(lhs));
    for(auto f: rhs.folders_)
        f->add_message(std::make_shared<Message>(rhs));
}