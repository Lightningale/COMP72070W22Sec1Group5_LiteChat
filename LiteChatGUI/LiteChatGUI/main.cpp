#include "LoginScreen.h"
#include "CreateAccount.h"
#include "ChatScreen.h"
#include "stdafx.h"
#include <QtWidgets>
#include <QStackedWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginScreen w;
    CreateAccount c;
    ChatScreen chat;
 
    //w.show();
    chat.show();



    // swtches screens in the same window
    // have to use this cus all screens are MainWindows
    //w.setCentralWidget(c.centralWidget());

    return a.exec();
}
