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
   

    // display message on chat screen
    void sender_message() {

        message = ui.messageBox->toPlainText();

        if (ui.RMessage8->text().isEmpty()) {

            if (ui.LMessage8->text().isEmpty()) {
                ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                ui.RMessage8->setText(message);
                return;
            }

            if (!ui.LMessage8->text().isEmpty()) {
                ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                ui.RMessage8->setText(message);

                if (ui.LMessage7->text().isEmpty() && ui.RMessage7->text().isEmpty()) {
                    ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                    ui.LMessage7->setText(ui.LMessage8->text());
                    ui.LMessage8->text().clear();
                    return;
                }
            }
        }

        if (ui.RMessage7->text().isEmpty()) {

            if (!ui.RMessage8->text().isEmpty()) {
                ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                ui.RMessage7->setText(ui.RMessage8->text());
                ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                ui.RMessage8->setText(message);
                return;
            }
            ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
            ui.RMessage8->setText(message);
            return;
        }

        if (ui.RMessage6->text().isEmpty()) {

            if (!ui.RMessage8->text().isEmpty()) {

                if (!ui.RMessage7->text().isEmpty()) {
                    ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                    ui.RMessage6->setText(ui.RMessage7->text());
                    ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                    ui.RMessage7->setText(ui.RMessage8->text());
                    ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                    ui.RMessage8->setText(message);
                    return;
                }
                ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                ui.RMessage7->setText(ui.RMessage8->text());
                ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                ui.RMessage8->setText(message);
                return;
            }

            ui.RMessage8->setText(message);
            return;
        }

        if (ui.RMessage5->text().isEmpty()) {

            if (!ui.RMessage8->text().isEmpty()) {

                if (!ui.RMessage7->text().isEmpty()) {

                    if (!ui.RMessage6->text().isEmpty()) {
                        ui.RMessage5->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage5->setText(ui.RMessage6->text());
                        ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage6->setText(ui.RMessage7->text());
                        ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage7->setText(ui.RMessage8->text());
                        ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage8->setText(message);
                        return;
                    }
                    ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                    ui.RMessage6->setText(ui.RMessage7->text());
                    ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                    ui.RMessage7->setText(ui.RMessage8->text());
                    ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                    ui.RMessage8->setText(message);
                    return;
                }
                ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                ui.RMessage7->setText(ui.RMessage8->text());
                ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                ui.RMessage8->setText(message);
                return;
            }
            ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
            ui.RMessage8->setText(message);
            return;

        }

        if (ui.RMessage4->text().isEmpty()) {

            if (!ui.RMessage8->text().isEmpty()) {

                if (!ui.RMessage7->text().isEmpty()) {

                    if (!ui.RMessage6->text().isEmpty()) {

                        if (!ui.RMessage5->text().isEmpty()) {
                            ui.RMessage4->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage4->setText(ui.RMessage5->text());
                            ui.RMessage5->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage5->setText(ui.RMessage6->text());
                            ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage6->setText(ui.RMessage7->text());
                            ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage7->setText(ui.RMessage8->text());
                            ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage8->setText(message);
                            return;
                        }
                        ui.RMessage5->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage5->setText(ui.RMessage6->text());
                        ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage6->setText(ui.RMessage7->text());
                        ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage7->setText(ui.RMessage8->text());
                        ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage8->setText(message);
                        return;
                    }
                    ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                    ui.RMessage6->setText(ui.RMessage7->text());
                    ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                    ui.RMessage7->setText(ui.RMessage8->text());
                    ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                    ui.RMessage8->setText(message);
                    return;
                }
                ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                ui.RMessage7->setText(ui.RMessage8->text());
                ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                ui.RMessage8->setText(message);
                return;
            }
            ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
            ui.RMessage8->setText(message);
            return;

        }

        if (ui.RMessage3->text().isEmpty()) {

            if (!ui.RMessage8->text().isEmpty()) {

                if (!ui.RMessage7->text().isEmpty()) {

                    if (!ui.RMessage6->text().isEmpty()) {

                        if (!ui.RMessage5->text().isEmpty()) {

                            if (!ui.RMessage4->text().isEmpty()) {

                                ui.RMessage3->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                ui.RMessage3->setText(ui.RMessage4->text());
                                ui.RMessage4->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                ui.RMessage4->setText(ui.RMessage5->text());
                                ui.RMessage5->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                ui.RMessage5->setText(ui.RMessage6->text());
                                ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                ui.RMessage6->setText(ui.RMessage7->text());
                                ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                ui.RMessage7->setText(ui.RMessage8->text());
                                ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                ui.RMessage8->setText(message);
                                return;
                            }
                            ui.RMessage4->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage4->setText(ui.RMessage5->text());
                            ui.RMessage5->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage5->setText(ui.RMessage6->text());
                            ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage6->setText(ui.RMessage7->text());
                            ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage7->setText(ui.RMessage8->text());
                            ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage8->setText(message);
                            return;
                        }
                        ui.RMessage5->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage5->setText(ui.RMessage6->text());
                        ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage6->setText(ui.RMessage7->text());
                        ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage7->setText(ui.RMessage8->text());
                        ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage8->setText(message);
                        return;
                    }
                    ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                    ui.RMessage6->setText(ui.RMessage7->text());
                    ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                    ui.RMessage7->setText(ui.RMessage8->text());
                    ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                    ui.RMessage8->setText(message);
                    return;
                }

                ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                ui.RMessage7->setText(ui.RMessage8->text());
                ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                ui.RMessage8->setText(message);
                return;
            } 
            ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
            ui.RMessage8->setText(message);
            return;

        }

        if (ui.RMessage2->text().isEmpty()) {

            if (!ui.RMessage8->text().isEmpty()) {

                if (!ui.RMessage7->text().isEmpty()) {

                    if (!ui.RMessage6->text().isEmpty()) {

                        if (!ui.RMessage5->text().isEmpty()) {

                            if (!ui.RMessage4->text().isEmpty()) {

                                if (!ui.RMessage3->text().isEmpty()) {
                                    ui.RMessage2->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                    ui.RMessage2->setText(ui.RMessage3->text());
                                    ui.RMessage3->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                    ui.RMessage3->setText(ui.RMessage4->text());
                                    ui.RMessage4->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                    ui.RMessage4->setText(ui.RMessage5->text());
                                    ui.RMessage5->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                    ui.RMessage5->setText(ui.RMessage6->text());
                                    ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                    ui.RMessage6->setText(ui.RMessage7->text());
                                    ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                    ui.RMessage7->setText(ui.RMessage8->text());
                                    ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                    ui.RMessage8->setText(message);
                                    return;
                                }
                                ui.RMessage3->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                ui.RMessage3->setText(ui.RMessage4->text());
                                ui.RMessage4->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                ui.RMessage4->setText(ui.RMessage5->text());
                                ui.RMessage5->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                ui.RMessage5->setText(ui.RMessage6->text());
                                ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                ui.RMessage6->setText(ui.RMessage7->text());
                                ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                ui.RMessage7->setText(ui.RMessage8->text());
                                ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                ui.RMessage8->setText(message);
                                return;
                            }
                            ui.RMessage4->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage4->setText(ui.RMessage5->text());
                            ui.RMessage5->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage5->setText(ui.RMessage6->text());
                            ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage6->setText(ui.RMessage7->text());
                            ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage7->setText(ui.RMessage8->text());
                            ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage8->setText(message);
                            return;
                        }
                        ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage5->setText(ui.RMessage6->text());
                        ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage6->setText(ui.RMessage7->text());
                        ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage7->setText(ui.RMessage8->text());
                        ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage8->setText(message);
                        return;
                    }
                    ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                    ui.RMessage6->setText(ui.RMessage7->text());
                    ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                    ui.RMessage7->setText(ui.RMessage8->text());
                    ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                    ui.RMessage8->setText(message);
                    return;
                }
                ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                ui.RMessage7->setText(ui.RMessage8->text());
                ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                ui.RMessage8->setText(message);
                return;
            }
            ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
            ui.RMessage8->setText(message);
            return;

        }

        if (ui.RMessage1->text().isEmpty()) {

            if (!ui.RMessage8->text().isEmpty()) {

                if (!ui.RMessage7->text().isEmpty()) {

                    if (!ui.RMessage6->text().isEmpty()) {

                        if (!ui.RMessage5->text().isEmpty()) {

                            if (!ui.RMessage4->text().isEmpty()) {

                                if (!ui.RMessage3->text().isEmpty()) {

                                    if (!ui.RMessage3->text().isEmpty()) {
                                        ui.RMessage1->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                        ui.RMessage1->setText(ui.RMessage2->text());
                                        ui.RMessage2->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                        ui.RMessage2->setText(ui.RMessage3->text());
                                        ui.RMessage3->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                        ui.RMessage3->setText(ui.RMessage4->text());
                                        ui.RMessage4->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                        ui.RMessage4->setText(ui.RMessage5->text());
                                        ui.RMessage5->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                        ui.RMessage5->setText(ui.RMessage6->text());
                                        ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                        ui.RMessage6->setText(ui.RMessage7->text());
                                        ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                        ui.RMessage7->setText(ui.RMessage8->text());
                                        ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                        ui.RMessage8->setText(message);
                                        return;
                                    }
                                    ui.RMessage2->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                    ui.RMessage2->setText(ui.RMessage3->text());
                                    ui.RMessage3->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                    ui.RMessage3->setText(ui.RMessage4->text());
                                    ui.RMessage4->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                    ui.RMessage4->setText(ui.RMessage5->text());
                                    ui.RMessage5->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                    ui.RMessage5->setText(ui.RMessage6->text());
                                    ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                    ui.RMessage6->setText(ui.RMessage7->text());
                                    ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                    ui.RMessage7->setText(ui.RMessage8->text());
                                    ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                    ui.RMessage8->setText(message);
                                    return;
                                }
                                ui.RMessage3->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                ui.RMessage3->setText(ui.RMessage4->text());
                                ui.RMessage4->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                ui.RMessage4->setText(ui.RMessage5->text());
                                ui.RMessage5->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                ui.RMessage5->setText(ui.RMessage6->text());
                                ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                ui.RMessage6->setText(ui.RMessage7->text());
                                ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                ui.RMessage7->setText(ui.RMessage8->text());
                                ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                                ui.RMessage8->setText(message);
                                return;
                            }
                            ui.RMessage4->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage4->setText(ui.RMessage5->text());
                            ui.RMessage5->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage5->setText(ui.RMessage6->text());
                            ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage6->setText(ui.RMessage7->text());
                            ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage7->setText(ui.RMessage8->text());\
                            ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                            ui.RMessage8->setText(message);
                            return;
                        }
                        ui.RMessage5->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage5->setText(ui.RMessage6->text());
                        ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage6->setText(ui.RMessage7->text());
                        ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage7->setText(ui.RMessage8->text());
                        ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                        ui.RMessage8->setText(message);
                        return;
                    }
                    ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                    ui.RMessage6->setText(ui.RMessage7->text());
                    ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                    ui.RMessage7->setText(ui.RMessage8->text());
                    ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                    ui.RMessage8->setText(message);
                    return;
                }
                ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                ui.RMessage7->setText(ui.RMessage8->text());
                ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
                ui.RMessage8->setText(message);
                return;
            }
            ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
            ui.RMessage8->setText(message);
            return;

        }
        else {
            ui.RMessage1->text().clear();
            ui.RMessage1->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
            ui.RMessage1->setText(ui.RMessage2->text());
            ui.RMessage2->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
            ui.RMessage2->setText(ui.RMessage3->text());
            ui.RMessage3->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
            ui.RMessage3->setText(ui.RMessage4->text());
            ui.RMessage4->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
            ui.RMessage4->setText(ui.RMessage5->text());
            ui.RMessage5->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
            ui.RMessage5->setText(ui.RMessage6->text());
            ui.RMessage6->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
            ui.RMessage6->setText(ui.RMessage7->text());
            ui.RMessage7->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
            ui.RMessage7->setText(ui.RMessage8->text());
            ui.RMessage8->setStyleSheet("QPushButton { background-color: rgb(0,185,0); border: 1px }");
            ui.RMessage8->setText(message);
            return;
        }

    }

private:
    Ui::ChatScreenClass ui;
};
