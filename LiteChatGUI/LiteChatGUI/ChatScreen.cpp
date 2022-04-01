#include "ChatScreen.h"
#include "stdafx.h"

ChatScreen::ChatScreen(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    connect(ui.sendButton, SIGNAL(clicked()), this, SLOT(sender_message()));
   
}