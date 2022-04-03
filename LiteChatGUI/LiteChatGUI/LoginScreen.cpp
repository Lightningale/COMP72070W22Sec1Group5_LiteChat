#include "LoginScreen.h"
#include "stdafx.h"

LoginScreen::LoginScreen(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.loginError->setVisible(false);
    ui.loginLabel->setVisible(false);
}
