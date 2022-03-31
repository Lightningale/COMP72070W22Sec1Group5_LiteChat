#include "LoginScreen.h"
#include "CreateAccount.h"
#include "stdafx.h"
#include <QtWidgets/QApplication>
#include <QStackedWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginScreen w;
    CreateAccount c;
    w.show();

    // swtches screens in the same window
    // have to use this cus all screens are MainWindows
    //w.setCentralWidget(c.centralWidget());

    return a.exec();
}
