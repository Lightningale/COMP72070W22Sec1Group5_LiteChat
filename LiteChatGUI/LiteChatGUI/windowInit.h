#pragma once

#include <QtWidgets>
#include "CreateAccount.h"
#include "LoginScreen.h"
#include "ChatScreen.h"

class windowInit : public QMainWindow
{
    Q_OBJECT

public:
    windowInit(QWidget* parent = Q_NULLPTR);

    LoginScreen l;
    CreateAccount c;
    ChatScreen s;

public slots:
    // login screen buttons
    void on_loginButton_clicked();
    void on_createButton_clicked();

    // create account buttons
    void on_backButton_clicked();
    void on_createAccButton_clicked();

private:
    QStackedWidget* screens;
};
