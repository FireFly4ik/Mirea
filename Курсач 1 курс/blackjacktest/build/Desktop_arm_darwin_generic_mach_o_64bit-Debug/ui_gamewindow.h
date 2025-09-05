/********************************************************************************
** Form generated from reading UI file 'gamewindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEWINDOW_H
#define UI_GAMEWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gameWindow
{
public:
    QGridLayout *gridLayout_2;
    QSpacerItem *beetwenDandA;
    QSpacerItem *beetwenDandG;
    QVBoxLayout *analyse;
    QHBoxLayout *buttons;
    QPushButton *split;
    QPushButton *add;
    QPushButton *stay;
    QVBoxLayout *gameButtons;
    QPushButton *nextGame;
    QPushButton *endGame;
    QSpacerItem *beetwenDandP;
    QWidget *playerHandWidget;
    QHBoxLayout *playerHands;
    QHBoxLayout *dealer;

    void setupUi(QWidget *gameWindow)
    {
        if (gameWindow->objectName().isEmpty())
            gameWindow->setObjectName("gameWindow");
        gameWindow->resize(1280, 720);
        gameWindow->setMinimumSize(QSize(1280, 720));
        gameWindow->setMaximumSize(QSize(1280, 720));
        QIcon icon;
        icon.addFile(QString::fromUtf8("images/icon.ico"), QSize(), QIcon::Mode::Normal, QIcon::State::Off);
        gameWindow->setWindowIcon(icon);
        gameWindow->setStyleSheet(QString::fromUtf8(""));
        gridLayout_2 = new QGridLayout(gameWindow);
        gridLayout_2->setObjectName("gridLayout_2");
        beetwenDandA = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(beetwenDandA, 0, 1, 1, 1);

        beetwenDandG = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        gridLayout_2->addItem(beetwenDandG, 0, 3, 1, 1);

        analyse = new QVBoxLayout();
        analyse->setObjectName("analyse");

        gridLayout_2->addLayout(analyse, 0, 0, 1, 1);

        buttons = new QHBoxLayout();
        buttons->setObjectName("buttons");
        buttons->setSizeConstraint(QLayout::SizeConstraint::SetMinimumSize);
        split = new QPushButton(gameWindow);
        split->setObjectName("split");
        split->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(split->sizePolicy().hasHeightForWidth());
        split->setSizePolicy(sizePolicy);

        buttons->addWidget(split);

        add = new QPushButton(gameWindow);
        add->setObjectName("add");
        sizePolicy.setHeightForWidth(add->sizePolicy().hasHeightForWidth());
        add->setSizePolicy(sizePolicy);

        buttons->addWidget(add);

        stay = new QPushButton(gameWindow);
        stay->setObjectName("stay");
        sizePolicy.setHeightForWidth(stay->sizePolicy().hasHeightForWidth());
        stay->setSizePolicy(sizePolicy);

        buttons->addWidget(stay);


        gridLayout_2->addLayout(buttons, 3, 0, 1, 5);

        gameButtons = new QVBoxLayout();
        gameButtons->setObjectName("gameButtons");
        nextGame = new QPushButton(gameWindow);
        nextGame->setObjectName("nextGame");
        nextGame->setEnabled(false);
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(nextGame->sizePolicy().hasHeightForWidth());
        nextGame->setSizePolicy(sizePolicy1);

        gameButtons->addWidget(nextGame);

        endGame = new QPushButton(gameWindow);
        endGame->setObjectName("endGame");
        sizePolicy1.setHeightForWidth(endGame->sizePolicy().hasHeightForWidth());
        endGame->setSizePolicy(sizePolicy1);

        gameButtons->addWidget(endGame);


        gridLayout_2->addLayout(gameButtons, 0, 4, 1, 1);

        beetwenDandP = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        gridLayout_2->addItem(beetwenDandP, 1, 2, 1, 1);

        playerHandWidget = new QWidget(gameWindow);
        playerHandWidget->setObjectName("playerHandWidget");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Preferred, QSizePolicy::Policy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(playerHandWidget->sizePolicy().hasHeightForWidth());
        playerHandWidget->setSizePolicy(sizePolicy2);
        playerHandWidget->setMaximumSize(QSize(1266, 16777215));
        playerHands = new QHBoxLayout(playerHandWidget);
        playerHands->setObjectName("playerHands");

        gridLayout_2->addWidget(playerHandWidget, 2, 0, 1, 5);

        dealer = new QHBoxLayout();
        dealer->setObjectName("dealer");

        gridLayout_2->addLayout(dealer, 0, 2, 1, 1);

        gridLayout_2->setRowStretch(0, 3);
        gridLayout_2->setRowStretch(1, 2);
        gridLayout_2->setRowStretch(2, 3);
        gridLayout_2->setRowStretch(3, 1);
        gridLayout_2->setColumnStretch(0, 2);
        gridLayout_2->setColumnStretch(1, 1);
        gridLayout_2->setColumnStretch(2, 3);
        gridLayout_2->setColumnStretch(3, 1);
        gridLayout_2->setColumnStretch(4, 2);

        retranslateUi(gameWindow);

        QMetaObject::connectSlotsByName(gameWindow);
    } // setupUi

    void retranslateUi(QWidget *gameWindow)
    {
        gameWindow->setWindowTitle(QCoreApplication::translate("gameWindow", "BlackJack", nullptr));
        split->setText(QCoreApplication::translate("gameWindow", "Split", nullptr));
        add->setText(QCoreApplication::translate("gameWindow", "Add", nullptr));
        stay->setText(QCoreApplication::translate("gameWindow", "Stay", nullptr));
        nextGame->setText(QCoreApplication::translate("gameWindow", "Next game", nullptr));
        endGame->setText(QCoreApplication::translate("gameWindow", "End game", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gameWindow: public Ui_gameWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEWINDOW_H
