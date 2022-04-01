#include "CreateAccount.h"
#include "stdafx.h"

CreateAccount::CreateAccount(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.loginError->setVisible(false);

    // take these, check if the username already exists in the database, if no, save this to database
    //QString username = ui.usernameBox->toPlainText();
    //QString password = ui.passwordBox_2->text();
}
