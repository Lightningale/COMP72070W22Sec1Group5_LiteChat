#include "LoginScreen.h"
#include "stdafx.h"

LoginScreen::LoginScreen(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.loginError->setVisible(false);

    //QString username = ui.usernameBox->toPlainText();
    //QString password = ui.passwordBox->text();
}
