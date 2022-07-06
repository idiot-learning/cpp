#include"message.h"
#include"folder.h"

int main()
{
    std::cout << "starting the program" <<std::endl;

    std::shared_ptr<Folder> folder_a(new Folder("folder_a"));
    std::shared_ptr<Message> a(new Message("this is the first message"));

    a->save(folder_a);
    a->print_folders();
    

    return 0;
}