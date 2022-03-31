#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_CreateAccount.h"

class CreateAccount : public QMainWindow
{
    Q_OBJECT

public:
    CreateAccount(QWidget* parent = Q_NULLPTR);

private:
    Ui::CreateAccountClass ui;
};
