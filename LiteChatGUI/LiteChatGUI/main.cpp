#include "windowInit.h"
#include "ChatScreen.h"
#include "stdafx.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    windowInit w;
    w.setFixedSize(1280, 720);
    w.show();
    
    // testing chat
    //ChatScreen chat;
    // // chat.resize(1280, 720);
    //chat.show();

    return a.exec();
    //return 1;
}
