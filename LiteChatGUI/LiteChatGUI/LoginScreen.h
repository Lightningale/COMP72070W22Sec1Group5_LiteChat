#pragma once

#include <QtWidgets>
#include "ui_LoginScreen.h"
#include <string>

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

    void readInput()
    {
        QString username = ui.usernameBox->toPlainText();
        QString password = ui.passwordBox->text();
    }

public slots:
    void on_loginButton_clicked()
    {
        // check if login details are correct here
        // if they are: run this snippet of code

        // if the username or password are incorrect
            // make loginError labelvisible

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
