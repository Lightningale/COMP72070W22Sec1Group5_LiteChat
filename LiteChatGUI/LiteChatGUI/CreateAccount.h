#pragma once

#include <QtWidgets>
#include "ui_CreateAccount.h"
#include <string>

class CreateAccount : public QMainWindow
{
    Q_OBJECT

public:
    CreateAccount(QWidget* parent = Q_NULLPTR);

    void readInput() {
        // take these, check if the username already exists in the database, if no, save this to database

        QString username = ui.usernameBox->toPlainText();
        QString password = ui.passwordBox_2->text();
    }

public slots:


private:
    Ui::CreateAccountClass ui;
};
