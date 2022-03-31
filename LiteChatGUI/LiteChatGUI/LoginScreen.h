#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LoginScreen.h"

class LoginScreen : public QMainWindow
{
    Q_OBJECT

public:
    LoginScreen(QWidget* parent = Q_NULLPTR);

    // running at all times when the window is up
    void execute()
    {
        connect(ui.loginButton, SIGNAL(clicked()), this, SLOT(on_loginButton_clicked()));

        connect(ui.createButton, SIGNAL(clicked()), this, SLOT(on_createText_clicked()));
    }

public slots:
    void on_loginButton_clicked()
    {
        // check if login details are correct here
        // if they are: run this snippet of code

        // temp check to make sure it works
        ui.loginButton->setText("clicked");
    }

    void on_createText_clicked()
    {
        // here should switch to the CreateAccount.ui screen
        ui.createButton->setText("something");
    }
private:
    Ui::LoginScreenClass ui;
};
