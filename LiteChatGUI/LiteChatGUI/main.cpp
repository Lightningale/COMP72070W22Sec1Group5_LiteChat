#include "windowInit.h"
#include "ChatScreen.h"
#include "stdafx.h"
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    windowInit w;
    ChatScreen chat;
    //w.setFixedSize(1280, 720);
    chat.resize(1280, 720);
 /*   w.show();*/

    // testing chat
    //ChatScreen chat;
    chat.show();

    return a.exec();
}
