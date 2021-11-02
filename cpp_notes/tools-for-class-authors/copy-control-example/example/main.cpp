#include"message.h"
#include"folder.h"

int main()
{
    Message a("this is the first message");
    Folder folder_a;
    a.save(folder_a);
    

    return 0;
}