#pragma once

#include <QtWidgets>
#include "ui_ChatScreen.h"
#include <string>

class ChatScreen : public QMainWindow
{
    Q_OBJECT

public:
    ChatScreen(QWidget* parent = Q_NULLPTR);

public slots:


private:
    Ui::ChatScreenClass ui;
};
