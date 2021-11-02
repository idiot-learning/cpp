#include "folder.h"
#include "message.h"

void Folder::add_message(Message *message) { messages_.insert(message); }

void Folder::remove_message(Message *message) { messages_.erase(message); }

void Folder::add_to_messages (const Folder &f)
{
    for(auto m: f.messages_)
    {
        m->add_folder(this);
    }
}

void Folder::remove_from_messages ()
{
    while(!messages_.empty())
    {
        (*messages_.begin())->remove(*this);
    }
}

Folder::Folder(const Folder &f):messages_{f.messages_}
{
    add_to_messages(f);
}

Folder::~Folder()
{
    remove_from_messages();
}

Folder& Folder::operator=(const Folder &f)
{
    remove_from_messages();
    messages_ = f.messages_;
    add_to_messages(f);
    return *this;
}