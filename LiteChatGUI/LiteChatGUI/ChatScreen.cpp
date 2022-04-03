#include "ChatScreen.h"
#include "stdafx.h"

ChatScreen::ChatScreen(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // everything on the right side is invisible at startup -> they will become visible when the user enters in a valid chatroom
    ui.noRoom->setVisible(false);
    ui.chatroomName->setVisible(false);
    ui.chatroomID->setVisible(false);
    ui.chatroomIDLabel->setVisible(false);
    ui.RecvMsgBox->setVisible(false);
    ui.RecvMsgSendButton->setVisible(false);

    // Set all the right side text message boxes transparent 
    ui.RMessage1->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.RMessage2->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.RMessage3->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.RMessage4->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.RMessage5->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.RMessage6->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.RMessage7->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.RMessage8->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");

    // Set all the left side text message boxes transparent 
    ui.LMessage1->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.LMessage2->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.LMessage3->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.LMessage4->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.LMessage5->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.LMessage6->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.LMessage7->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    ui.LMessage8->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");

}