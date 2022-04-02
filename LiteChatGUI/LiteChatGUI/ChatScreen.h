#pragma once

#include <QtWidgets>
#include "ui_ChatScreen.h"
#include <string>

class ChatScreen : public QMainWindow
{
    Q_OBJECT
    QString message;
public:
    ChatScreen(QWidget* parent = Q_NULLPTR);


public slots:
   

    // display sender messages on chat screen
    void sender_messages() {

        message = ui.messageBox->toPlainText();
        ui.messageBox->clear();

        ui.RMessage1->setText(ui.RMessage2->text());
        ui.RMessage2->setText("");
        ui.RMessage2->setText(ui.RMessage3->text());
        ui.RMessage3->setText("");
        ui.RMessage3->setText(ui.RMessage4->text());
        ui.RMessage4->setText("");
        ui.RMessage4->setText(ui.RMessage5->text());
        ui.RMessage5->setText("");
        ui.RMessage5->setText(ui.RMessage6->text());
        ui.RMessage6->setText("");
        ui.RMessage6->setText(ui.RMessage7->text());
        ui.RMessage7->setText("");
        ui.RMessage7->setText(ui.RMessage8->text());
        ui.RMessage8->setText("");

        ui.LMessage1->setText(ui.LMessage2->text());
        ui.LMessage2->setText("");
        ui.LMessage2->setText(ui.LMessage3->text());
        ui.LMessage3->setText("");
        ui.LMessage3->setText(ui.LMessage4->text());
        ui.LMessage4->setText("");
        ui.LMessage4->setText(ui.LMessage5->text());
        ui.LMessage5->setText("");
        ui.LMessage5->setText(ui.LMessage6->text());
        ui.LMessage6->setText("");
        ui.LMessage6->setText(ui.LMessage7->text());
        ui.LMessage7->setText("");
        ui.LMessage7->setText(ui.LMessage8->text());
        ui.LMessage8->setText("");

        ui.RMessage8->setText(message);

        // Check Right Side
        if (!ui.RMessage8->text().isEmpty()) {
            ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
        }
        else {
            ui.RMessage8->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.RMessage7->text().isEmpty()) {
            ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
        }
        else {
            ui.RMessage7->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.RMessage6->text().isEmpty()) {
            ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
        }else{
            ui.RMessage6->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.RMessage5->text().isEmpty()) {
            ui.RMessage5->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
        }
        else {
            ui.RMessage5->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.RMessage4->text().isEmpty()) {
            ui.RMessage4->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
        }
        else {
            ui.RMessage4->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.RMessage3->text().isEmpty()) {
            ui.RMessage3->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
        }
        else {
            ui.RMessage3->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.RMessage2->text().isEmpty()) {
            ui.RMessage2->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
        }
        else {
            ui.RMessage2->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.RMessage1->text().isEmpty()) {
            ui.RMessage1->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
        }else{
            ui.RMessage1->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        // Check Left Side
        if (!ui.LMessage8->text().isEmpty()) {
            ui.LMessage8->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
        }
        else {
            ui.LMessage8->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.LMessage7->text().isEmpty()) {
            ui.LMessage7->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
        }
        else {
            ui.LMessage7->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.LMessage6->text().isEmpty()) {
            ui.LMessage6->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
        }
        else {
            ui.LMessage6->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.LMessage5->text().isEmpty()) {
            ui.LMessage5->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
        }
        else {
            ui.LMessage5->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.LMessage4->text().isEmpty()) {
            ui.LMessage4->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
        }
        else {
            ui.LMessage4->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.LMessage3->text().isEmpty()) {
            ui.LMessage3->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
        }else{
            ui.LMessage3->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.LMessage2->text().isEmpty()) {
            ui.LMessage2->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
        }else{
            ui.LMessage2->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.LMessage1->text().isEmpty()) {
            ui.LMessage1->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
        }else{
            ui.LMessage1->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        ui.LMessage8->setText("");
    }
 
    // display receive messages on chat screen
    void receive_messages() {

        message = ui.RecvMsgBox->toPlainText();
        ui.RecvMsgBox->clear();

        ui.RMessage1->setText(ui.RMessage2->text());
        ui.RMessage2->setText("");
        ui.RMessage2->setText(ui.RMessage3->text());
        ui.RMessage3->setText("");
        ui.RMessage3->setText(ui.RMessage4->text());
        ui.RMessage4->setText("");
        ui.RMessage4->setText(ui.RMessage5->text());
        ui.RMessage5->setText("");
        ui.RMessage5->setText(ui.RMessage6->text());
        ui.RMessage6->setText("");
        ui.RMessage6->setText(ui.RMessage7->text());
        ui.RMessage7->setText("");
        ui.RMessage7->setText(ui.RMessage8->text());
        ui.RMessage8->setText("");

        ui.LMessage1->setText(ui.LMessage2->text());
        ui.LMessage2->setText("");
        ui.LMessage2->setText(ui.LMessage3->text());
        ui.LMessage3->setText("");
        ui.LMessage3->setText(ui.LMessage4->text());
        ui.LMessage4->setText("");
        ui.LMessage4->setText(ui.LMessage5->text());
        ui.LMessage5->setText("");
        ui.LMessage5->setText(ui.LMessage6->text());
        ui.LMessage6->setText("");
        ui.LMessage6->setText(ui.LMessage7->text());
        ui.LMessage7->setText("");
        ui.LMessage7->setText(ui.LMessage8->text());
        ui.LMessage8->setText("");

        ui.LMessage8->setText(message);
        

        // Check Right Side
        if (!ui.RMessage8->text().isEmpty()) {
            ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
        }
        else {
            ui.RMessage8->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.RMessage7->text().isEmpty()) {
            ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
        }
        else {
            ui.RMessage7->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.RMessage6->text().isEmpty()) {
            ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
        }
        else {
            ui.RMessage6->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.RMessage5->text().isEmpty()) {
            ui.RMessage5->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
        }
        else {
            ui.RMessage5->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.RMessage4->text().isEmpty()) {
            ui.RMessage4->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
        }
        else {
            ui.RMessage4->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.RMessage3->text().isEmpty()) {
            ui.RMessage3->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
        }
        else {
            ui.RMessage3->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.RMessage2->text().isEmpty()) {
            ui.RMessage2->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
        }
        else {
            ui.RMessage2->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.RMessage1->text().isEmpty()) {
            ui.RMessage1->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
        }
        else {
            ui.RMessage1->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        // Check Left Side
        if (!ui.LMessage8->text().isEmpty()) {
            ui.LMessage8->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
        }
        else {
            ui.LMessage8->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.LMessage7->text().isEmpty()) {
            ui.LMessage7->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
        }
        else {
            ui.LMessage7->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.LMessage6->text().isEmpty()) {
            ui.LMessage6->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
        }
        else {
            ui.LMessage6->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.LMessage5->text().isEmpty()) {
            ui.LMessage5->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
        }
        else {
            ui.LMessage5->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.LMessage4->text().isEmpty()) {
            ui.LMessage4->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
        }
        else {
            ui.LMessage4->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.LMessage3->text().isEmpty()) {
            ui.LMessage3->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
        }
        else {
            ui.LMessage3->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.LMessage2->text().isEmpty()) {
            ui.LMessage2->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
        }
        else {
            ui.LMessage2->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        if (!ui.LMessage1->text().isEmpty()) {
            ui.LMessage1->setStyleSheet("QPushButton { background-color: rgb(255,255,255); border: 1px }");
        }
        else {
            ui.LMessage1->setStyleSheet("QPushButton { background-color: transparent; border: 1px }");
        }

        ui.RMessage8->setText("");
    }
private:
    Ui::ChatScreenClass ui;
};
