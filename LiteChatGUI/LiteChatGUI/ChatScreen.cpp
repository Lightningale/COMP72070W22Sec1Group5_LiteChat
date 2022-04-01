#include "ChatScreen.h"
#include "stdafx.h"

ChatScreen::ChatScreen(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.sendButton, SIGNAL(clicked()), this, SLOT(sender_message()));

    ui.RMessage1->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.RMessage2->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.RMessage3->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.RMessage4->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.RMessage5->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.RMessage6->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.RMessage7->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.RMessage8->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
}