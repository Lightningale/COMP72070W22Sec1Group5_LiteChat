#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LoginScreen.h"

class LoginScreen : public QMainWindow
{
    Q_OBJECT

public:
    LoginScreen(QWidget *parent = Q_NULLPTR);

private:
    Ui::LoginScreenClass ui;
};
