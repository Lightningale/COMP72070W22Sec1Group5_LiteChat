#include "CreateAccount.h"
#include "stdafx.h"

CreateAccount::CreateAccount(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    ui.loginError->setVisible(false);
    ui.accountCreatedLabel->setVisible(false);
    
}
