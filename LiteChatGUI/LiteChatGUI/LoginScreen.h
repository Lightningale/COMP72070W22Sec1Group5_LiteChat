#pragma once

#include <QtWidgets>
#include "ui_LoginScreen.h"

class LoginScreen : public QMainWindow
{
    Q_OBJECT

public:
    LoginScreen(QWidget* parent = Q_NULLPTR);

    Ui::LoginScreenClass ui;

public slots:
   
};
