#include "windowInit.h"
#include "stdafx.h"
#include "ClientFunctions.h"

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
    // 
    // button connects
    // login page
    connect(l.ui.loginButton, SIGNAL(clicked()), this, SLOT(on_loginButton_clicked()));
    connect(l.ui.createButton, SIGNAL(clicked()), this, SLOT(on_createButton_clicked()));
    connect(l.ui.exitButton, SIGNAL(clicked()), this, SLOT(on_exitButton_clicked()));

    // create account page
    connect(c.ui.backButton, SIGNAL(clicked()), this, SLOT(on_backButton_clicked()));
    connect(c.ui.createAccButton, SIGNAL(clicked()), this, SLOT(on_createAccButton_clicked()));
    
    // chat page
    connect(s.ui.logoutButton, SIGNAL(clicked()), this, SLOT(on_logoutButton_clicked()));
    connect(s.ui.searchRoomsButton, SIGNAL(clicked()), this, SLOT(on_searchButton_clicked()));
    connect(s.ui.createChatroomButton, SIGNAL(clicked()), this, SLOT(on_createChatroomButton_clicked()));
    connect(s.ui.sendButton, SIGNAL(clicked()), this, SLOT(sender_messages()));
    connect(s.ui.RecvMsgSendButton, SIGNAL(clicked()), this, SLOT(receive_messages()));
    connect(s.ui.leaveRoomButton, SIGNAL(clicked()), this, SLOT(on_leaveRoomButton_clicked()));

    //connect(s.ui.sendButton, SIGNAL(clicked()), this, SLOT(()));
    //connect(s.ui.sendImage, SIGNAL(clicked()), this, SLOT(()));

    createClientConn();
}


int windowInit::createClientConn()
{
    //starts Winsock DLLs
    WSADATA wsaData;
    if ((WSAStartup(MAKEWORD(2, 2), &wsaData)) != 0) {
        return 0;
    }

    //initializes socket. SOCK_STREAM: TCP
    ClientSocket;
    ClientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (ClientSocket == INVALID_SOCKET) {
        WSACleanup();
        return 0;
    }

    //Connect socket to specified server
    sockaddr_in SvrAddr;
    SvrAddr.sin_family = AF_INET;						//Address family type itnernet
    SvrAddr.sin_port = htons(27000);					//port (host to network conversion)
    SvrAddr.sin_addr.s_addr = inet_addr("127.0.0.1");	//IP address
    if ((::connect(ClientSocket, (struct sockaddr*)&SvrAddr, sizeof(SvrAddr))) == SOCKET_ERROR) {
        closesocket(ClientSocket);
        WSACleanup();
        return 0;
    }
    ///////////////////////////////////
    currentState = ClientState::Welcome;
    cursorC = 0;
    //errorFlag = 0;


    //::thread UIthread(ClientSocket);
    ::thread ReceivingThread(recvResponse, ClientSocket);
    
   // UIthread.join();
   // ReceivingThread.join();

    ReceivingThread.detach();

}




// login screen buttons
void windowInit::on_loginButton_clicked()
{
    // get input from text fields
    // check if login details are correct here
    // stores user input from text field and converts to a char array
    QString user = l.ui.usernameBox->toPlainText();
    QByteArray u = user.toLocal8Bit();
    strcpy(username, u.data());

    QString pass = l.ui.passwordBox->text();
    QByteArray p = pass.toLocal8Bit();
    strcpy(password, p.data());

    RegisterLogin(ClientSocket, username, password, 1);

    // if the username or password are incorrect
        // make loginError labelvisible
    if (errorFlag == 1)
    {
        l.ui.loginError->setVisible(true);
    }
    else if(errorFlag == 0)
    {
        l.ui.loginLabel->setVisible(true);
        
        // pre-reset in case of dupes
        clearChatroomList();
        clearMemberList();
        clearChatSide();

        ::this_thread::sleep_for(::chrono::milliseconds(2000));   // sleep in case the thread needs to populate the next page

        // when the login information is correct the chatroom window will be populated based on the logged in user
        currentState = ClientState::Lobby;

        // populate next chatroom window
        s.ui.clientUser->setText(u);

        // populate chatroom list
        populateChatroomList();

        // clear boxes
        l.ui.loginError->setVisible(false);
        l.ui.usernameBox->clear();
        l.ui.passwordBox->clear();

        screens->setCurrentIndex(2);
    }
    l.update();
}

void windowInit::on_createButton_clicked()
{
    // clear boxes
    l.ui.usernameBox->clear();
    l.ui.passwordBox->clear();

    l.ui.loginError->setVisible(false);

    // here should switch to the CreateAccount.ui screen
    screens->setCurrentIndex(1);
}

void windowInit::on_exitButton_clicked()
{
    // close window
    //closes connection and socket
    closesocket(ClientSocket);

    //frees Winsock DLL resources
    WSACleanup();

    windowInit::close();
}

// create account screen buttons
void windowInit::on_backButton_clicked()
{
    // clear boxes
    c.ui.usernameBox->clear();
    c.ui.passwordBox_2->clear();

    c.ui.loginError->setVisible(false);
    c.ui.accountCreatedLabel->setVisible(false);

    screens->setCurrentIndex(0);
}

void windowInit::on_createAccButton_clicked()
{
    char createUser[usernameLength] = { '\0' };
    char createPass[passwordLength] = { '\0' };

    // get input from text fields
    QString user = c.ui.usernameBox->toPlainText();
    QByteArray u = user.toLocal8Bit();
    strcpy(createUser, u.data());

    QString pass = c.ui.passwordBox_2->text();
    QByteArray p = pass.toLocal8Bit();
    strcpy(createPass, p.data());

    // send to server to check
    RegisterLogin(ClientSocket, createUser, createPass, 0);
    // server returns something

    if (errorFlag == 1)         // if the username is taken
    {
        c.ui.loginError->setVisible(true);
        c.ui.accountCreatedLabel->setVisible(false);
    }
    else if (errorFlag == 0)        // if the account creation is successful -> should save to database
    {
        c.ui.loginError->setVisible(false);
        c.ui.accountCreatedLabel->setVisible(true);
    }
    c.update();
}


// chat screen
void windowInit::on_logoutButton_clicked()
{
    currentState = ClientState::Welcome;
    // return to login screen
    // log user out
    l.ui.loginLabel->setVisible(false);
    RegisterLogin(ClientSocket, username, password, 2);
    screens->setCurrentIndex(0);
    l.update();


    // clear screens
    clearChatSide();

    clearChatroomList();
    clearMemberList();
    s.ui.messageBox->clear();

}

void windowInit::on_searchButton_clicked()
{
    QString search = s.ui.userSearch->toPlainText();
    chatroomRn = search.toLong();

    JoinChatroom(ClientSocket, chatroomRn);


    if (errorFlag == 3 && (currentState == ClientState::Lobby))
    {
        s.ui.noRoom->setVisible(true);
    }
    else if (errorFlag == 0 && (currentState == ClientState::Lobby))
    {
        currentState = ClientState::Chatroom;
        // pre clear list
        clearChatroomList();
        clearMemberList();
        // display room members
        populateChatroomList();
        populateChatroomMembers();
        //displayChatroomMessages();

        //set top bar items
        s.ui.chatroomName->setText(chatroomList[chatroomRn].chatroomName);
        QString roomID = QString::number(chatroomList[chatroomRn].chatroomID);
        s.ui.chatroomID->setText(roomID);
        s.ui.chatroomName->setVisible(true);
        s.ui.chatroomID->setVisible(true);
        s.ui.chatroomIDLabel->setVisible(true);
        s.ui.leaveRoomButton->setVisible(true);
    }

    s.ui.userSearch->clear();
    s.update();
}

void windowInit::on_createChatroomButton_clicked()
{
    char newRoom[chatroomNameSize] = { 0 };
    if (!s.ui.newChatroomName->toPlainText().isEmpty())
    {
        QString chatroom = s.ui.newChatroomName->toPlainText();
        QByteArray cr = chatroom.toLocal8Bit();
        strcpy(newRoom, cr.data());
    }
    else
        strcpy(newRoom, "Chatroom" + chatroomList.size());

    CreateChatroom(ClientSocket, username, newRoom);
    populateChatroomList();

    s.ui.newChatroomName->clear();
    s.update();
}

void windowInit::on_sendButton_clicked()
{
    char msg[messageLength] = { 0 };
    // send current message
    QString rawMsg = s.ui.messageBox->toPlainText();
    QByteArray m = rawMsg.toLocal8Bit();
    strcpy(msg, m.data());

    SendChatMessage(ClientSocket, currentUser.username, currentChatroom.chatroomID, msg);

    s.ui.messageBox->clear();
}

void windowInit::on_sendImage_clicked()
{
    // send image
    // prompt user to upload pic from library
    // OR use the directory in the chat bar to search for image
}

void windowInit::on_leaveRoomButton_clicked()
{
    currentState = ClientState::Lobby;
    clearChatSide();
    clearMemberList();
}


// display sender messages on chat screen
void windowInit::sender_messages() 
{
    QString message = s.ui.messageBox->toPlainText();
    s.ui.messageBox->clear();

    s.ui.RMessage1->setText(s.ui.RMessage2->text());
    s.ui.RMessage2->setText("");
    s.ui.RMessage2->setText(s.ui.RMessage3->text());
    s.ui.RMessage3->setText("");
    s.ui.RMessage3->setText(s.ui.RMessage4->text());
    s.ui.RMessage4->setText("");
    s.ui.RMessage4->setText(s.ui.RMessage5->text());
    s.ui.RMessage5->setText("");
    s.ui.RMessage5->setText(s.ui.RMessage6->text());
    s.ui.RMessage6->setText("");
    s.ui.RMessage6->setText(s.ui.RMessage7->text());
    s.ui.RMessage7->setText("");
    s.ui.RMessage7->setText(s.ui.RMessage8->text());
    s.ui.RMessage8->setText("");

    s.ui.LMessage1->setText(s.ui.LMessage2->text());
    s.ui.LMessage2->setText("");
    s.ui.LMessage2->setText(s.ui.LMessage3->text());
    s.ui.LMessage3->setText("");
    s.ui.LMessage3->setText(s.ui.LMessage4->text());
    s.ui.LMessage4->setText("");
    s.ui.LMessage4->setText(s.ui.LMessage5->text());
    s.ui.LMessage5->setText("");
    s.ui.LMessage5->setText(s.ui.LMessage6->text());
    s.ui.LMessage6->setText("");
    s.ui.LMessage6->setText(s.ui.LMessage7->text());
    s.ui.LMessage7->setText("");
    s.ui.LMessage7->setText(s.ui.LMessage8->text());
    s.ui.LMessage8->setText("");

    s.ui.RMessage8->setText(message);

    // Check Right Side
    if (!s.ui.RMessage8->text().isEmpty()) {
        s.ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
    }
    else {
        s.ui.RMessage8->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.RMessage7->text().isEmpty()) {
        s.ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
    }
    else {
        s.ui.RMessage7->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.RMessage6->text().isEmpty()) {
        s.ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
    }
    else {
        s.ui.RMessage6->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.RMessage5->text().isEmpty()) {
        s.ui.RMessage5->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
    }
    else {
        s.ui.RMessage5->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.RMessage4->text().isEmpty()) {
        s.ui.RMessage4->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
    }
    else {
        s.ui.RMessage4->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.RMessage3->text().isEmpty()) {
        s.ui.RMessage3->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
    }
    else {
        s.ui.RMessage3->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.RMessage2->text().isEmpty()) {
        s.ui.RMessage2->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
    }
    else {
        s.ui.RMessage2->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.RMessage1->text().isEmpty()) {
        s.ui.RMessage1->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
    }
    else {
        s.ui.RMessage1->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    // Check Left Side
    if (!s.ui.LMessage8->text().isEmpty()) {
        s.ui.LMessage8->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
    }
    else {
        s.ui.LMessage8->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.LMessage7->text().isEmpty()) {
        s.ui.LMessage7->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
    }
    else {
        s.ui.LMessage7->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.LMessage6->text().isEmpty()) {
        s.ui.LMessage6->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
    }
    else {
        s.ui.LMessage6->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.LMessage5->text().isEmpty()) {
        s.ui.LMessage5->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
    }
    else {
        s.ui.LMessage5->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.LMessage4->text().isEmpty()) {
        s.ui.LMessage4->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
    }
    else {
        s.ui.LMessage4->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.LMessage3->text().isEmpty()) {
        s.ui.LMessage3->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
    }
    else {
        s.ui.LMessage3->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.LMessage2->text().isEmpty()) {
        s.ui.LMessage2->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
    }
    else {
        s.ui.LMessage2->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.LMessage1->text().isEmpty()) {
        s.ui.LMessage1->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
    }
    else {
        s.ui.LMessage1->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    s.ui.LMessage8->setText("");
}

// display receive messages on chat screen
void windowInit::receive_messages() 
{

    QString message = s.ui.RecvMsgBox->toPlainText();
    s.ui.RecvMsgBox->clear();

    s.ui.RMessage1->setText(s.ui.RMessage2->text());
    s.ui.RMessage2->setText("");
    s.ui.RMessage2->setText(s.ui.RMessage3->text());
    s.ui.RMessage3->setText("");
    s.ui.RMessage3->setText(s.ui.RMessage4->text());
    s.ui.RMessage4->setText("");
    s.ui.RMessage4->setText(s.ui.RMessage5->text());
    s.ui.RMessage5->setText("");
    s.ui.RMessage5->setText(s.ui.RMessage6->text());
    s.ui.RMessage6->setText("");
    s.ui.RMessage6->setText(s.ui.RMessage7->text());
    s.ui.RMessage7->setText("");
    s.ui.RMessage7->setText(s.ui.RMessage8->text());
    s.ui.RMessage8->setText("");

    s.ui.LMessage1->setText(s.ui.LMessage2->text());
    s.ui.LMessage2->setText("");
    s.ui.LMessage2->setText(s.ui.LMessage3->text());
    s.ui.LMessage3->setText("");
    s.ui.LMessage3->setText(s.ui.LMessage4->text());
    s.ui.LMessage4->setText("");
    s.ui.LMessage4->setText(s.ui.LMessage5->text());
    s.ui.LMessage5->setText("");
    s.ui.LMessage5->setText(s.ui.LMessage6->text());
    s.ui.LMessage6->setText("");
    s.ui.LMessage6->setText(s.ui.LMessage7->text());
    s.ui.LMessage7->setText("");
    s.ui.LMessage7->setText(s.ui.LMessage8->text());
    s.ui.LMessage8->setText("");

    s.ui.LMessage8->setText(message);


    // Check Right Side
    if (!s.ui.RMessage8->text().isEmpty()) {
        s.ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
    }
    else {
        s.ui.RMessage8->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.RMessage7->text().isEmpty()) {
        s.ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
    }
    else {
        s.ui.RMessage7->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.RMessage6->text().isEmpty()) {
        s.ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
    }
    else {
        s.ui.RMessage6->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.RMessage5->text().isEmpty()) {
        s.ui.RMessage5->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
    }
    else {
        s.ui.RMessage5->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.RMessage4->text().isEmpty()) {
        s.ui.RMessage4->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
    }
    else {
        s.ui.RMessage4->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.RMessage3->text().isEmpty()) {
        s.ui.RMessage3->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
    }
    else {
        s.ui.RMessage3->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.RMessage2->text().isEmpty()) {
        s.ui.RMessage2->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
    }
    else {
        s.ui.RMessage2->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.RMessage1->text().isEmpty()) {
        s.ui.RMessage1->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
    }
    else {
        s.ui.RMessage1->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    // Check Left Side
    if (!s.ui.LMessage8->text().isEmpty()) {
        s.ui.LMessage8->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
    }
    else {
        s.ui.LMessage8->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.LMessage7->text().isEmpty()) {
        s.ui.LMessage7->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
    }
    else {
        s.ui.LMessage7->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.LMessage6->text().isEmpty()) {
        s.ui.LMessage6->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
    }
    else {
        s.ui.LMessage6->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.LMessage5->text().isEmpty()) {
        s.ui.LMessage5->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
    }
    else {
        s.ui.LMessage5->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.LMessage4->text().isEmpty()) {
        s.ui.LMessage4->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
    }
    else {
        s.ui.LMessage4->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.LMessage3->text().isEmpty()) {
        s.ui.LMessage3->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
    }
    else {
        s.ui.LMessage3->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.LMessage2->text().isEmpty()) {
        s.ui.LMessage2->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
    }
    else {
        s.ui.LMessage2->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    if (!s.ui.LMessage1->text().isEmpty()) {
        s.ui.LMessage1->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
    }
    else {
        s.ui.LMessage1->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
    }

    s.ui.RMessage8->setText("");
}

void windowInit::populateChatroomList()
{
    s.ui.listofchatrooms->clear();
    for (int i = 0; i < chatroomList.size(); i++)
    {
        s.ui.listofchatrooms->addItem(chatroomList[i].chatroomName);
    }
    s.update();
}

void windowInit::populateChatroomMembers()
{
    s.ui.memberList->clear();
    for (int i = 0; i < chatroomMessageMap[chatroomRn].size(); i++)
    {
        s.ui.memberList->addItem(chatroomMemberMap[chatroomRn][i].username);
    }
    s.update();
}

void windowInit::displayChatroomMessages()
{
    //DisplayMessage(chatroomMessageMap[currentChatroom.chatroomID][i]);
}

void windowInit::clearChatroomList()
{
    int items = s.ui.listofchatrooms->count();

    while (items > 0)
    {
        s.ui.listofchatrooms->takeItem(items);
        items--;
    }
    s.update();
}

void windowInit::clearMemberList()
{
    int items = s.ui.memberList->count();

    while (items > 0)
    {
        s.ui.memberList->takeItem(items);
        items--;
    }
    s.update();
}

void windowInit::clearChatSide()
{
    // everything on the right side is invisible at startup -> they will become visible when the user enters in a valid chatroom
    s.ui.noRoom->setVisible(false);
    s.ui.chatroomName->setVisible(false);
    s.ui.chatroomID->setVisible(false);
    s.ui.chatroomIDLabel->setVisible(false);
    s.ui.RecvMsgBox->setVisible(false);
    s.ui.RecvMsgSendButton->setVisible(false);
    s.ui.leaveRoomButton->setVisible(false);

    // make chat boxes invis + clear
}