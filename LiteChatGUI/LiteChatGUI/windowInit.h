#pragma once
#include <windows.networking.sockets.h>
#pragma comment(lib, "Ws2_32.lib")
#include <QtWidgets>
#include "CreateAccount.h"
#include "LoginScreen.h"
#include "ChatScreen.h"
#include "Packet.h"

class windowInit : public QMainWindow
{
    Q_OBJECT

public:
    windowInit(QWidget* parent = Q_NULLPTR);
    
    int createClientConn();

    LoginScreen l;
    CreateAccount c;
    ChatScreen s;

public slots:
    // login screen buttons
    void on_loginButton_clicked();
    void on_createButton_clicked();
    void on_exitButton_clicked();

    // create account buttons
    void on_backButton_clicked();
    void on_createAccButton_clicked();


    // chat screen buttons
    void on_logoutButton_clicked();
    void on_searchButton_clicked();
    void on_createChatroomButton_clicked();
    void on_sendButton_clicked();
    void on_sendImage_clicked();


    // chat screen other
    void sender_messages();
    void receive_messages();
    void populateChatroomList();
private:
    QStackedWidget* screens;
    char username[usernameLength] = { '\0' };   // stores username
    char password[passwordLength] = { '\0' };   // stores password
};
