#include "windowInit.h"
#include "stdafx.h"

// Main window
windowInit::windowInit(QWidget* parent)
    : QMainWindow(parent)
{   
    // setup
    screens = new QStackedWidget(this);
    screens->addWidget(l.centralWidget());  //login
    screens->addWidget(c.centralWidget());  //create
    screens->addWidget(s.centralWidget());  //chats

    screens->setCurrentIndex(0);
    setCentralWidget(screens);

    /////////////////////////////////////////////////////////////////////

    // button connects
    // login page
    connect(l.ui.loginButton, SIGNAL(clicked()), this, SLOT(on_loginButton_clicked()));
    connect(l.ui.createButton, SIGNAL(clicked()), this, SLOT(on_createButton_clicked()));

    // create account page
    connect(c.ui.backButton, SIGNAL(clicked()), this, SLOT(on_backButton_clicked()));
    connect(c.ui.createAccButton, SIGNAL(clicked()), this, SLOT(on_createAccButton_clicked()));
}

// login screen buttons
void windowInit::on_loginButton_clicked()
{
    // check if login details are correct here
    // if they are: run this snippet of code
    screens->setCurrentIndex(2);

    // if the username or password are incorrect
        // make loginError labelvisible
}

void windowInit::on_createButton_clicked()
{
    // here should switch to the CreateAccount.ui screen
    screens->setCurrentIndex(1);
}



// create account screen buttons
void windowInit::on_backButton_clicked()
{
    screens->setCurrentIndex(0);
}

void windowInit::on_createAccButton_clicked()
{
    // check if login details are correct here
    // if they are: run this snippet of code

    // if the username or password are incorrect
        // make loginError labelvisible

    c.ui.createAccButton->setText("clicked");
    c.ui.loginError->setVisible(true);
}