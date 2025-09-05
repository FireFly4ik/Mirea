#include "gamewindow.h"
#include "ui_gamewindow.h"
#include "playGame.h"
#include "analys.h"

#include <QLayout>
#include <QLabel>
#include <QDialog>
#include <QDebug>

vector<QHBoxLayout*> allPlayerHandsLayouts;
int activeHandIndexLayout;
Ui::gameWindow* windowUI;
QHBoxLayout* layoutToAdd;
QLabel* gamesLabel = nullptr;
QLabel* cardsLabel = nullptr;
QLabel* winsLabel = nullptr;
QLabel* chanceLabel = nullptr;
vector<QLabel*> playerScoreLabels;
QLabel* dealerScoreLabel = nullptr;

void startGame();

void dealerStartUI();
void dealerEndUI();

void add();
void stay();
void split();
void newGame();
void endGame();

void addHand();
void clearLayout();
void clearLayouts();
void styleCardLabel(QLabel* label, QString text);
void checkAnalys();
void updateAnalys();
void updateChance();

gameWindow::gameWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::gameWindow)
{
    windowUI = ui;
    ui->setupUi(this);
    this->setWindowTitle("WhiteJimmy");

    createGame();

    startGame();

    connect(ui->add, &QPushButton::clicked, this, add);
    connect(ui->stay, &QPushButton::clicked, this, stay);
    connect(ui->split, &QPushButton::clicked, this, split);
    connect(ui->nextGame, &QPushButton::clicked, this, newGame);
    connect(ui->endGame, &QPushButton::clicked, this, &gameWindow::endGame);

    QVBoxLayout* analysLayout = windowUI->analyse;

    gamesLabel = new QLabel();
    cardsLabel = new QLabel();
    winsLabel = new QLabel();
    chanceLabel = new QLabel();

    analysLayout->addWidget(chanceLabel);
    analysLayout->addWidget(gamesLabel);
    analysLayout->addWidget(cardsLabel);
    analysLayout->addWidget(winsLabel);
    updateChance();
    updateAnalys();

    gamesLabel->setStyleSheet("font-size: 16px; font-weight: bold; color: white; font-weight: bold;");
    cardsLabel->setStyleSheet("font-size: 14px; color: white; font-weight: bold;");
    winsLabel->setStyleSheet("font-size: 14px; color: white; font-weight: bold;");
    chanceLabel->setStyleSheet("font-size: 16px; color: white; font-weight: bold;");
    QString buttonStyle = "QPushButton { background-color: #444; color: white; padding: 8px; border-radius: 6px; }"
                          "QPushButton:hover { background-color: #555; }"
                          "QPushButton:disabled { background-color: #222; color: gray; }";

    ui->add->setStyleSheet(buttonStyle);
    ui->stay->setStyleSheet(buttonStyle);
    ui->split->setStyleSheet(buttonStyle);
    ui->nextGame->setStyleSheet(buttonStyle);
    ui->endGame->setStyleSheet(buttonStyle);
    this->setStyleSheet("background-color: #222;");

}

void updateChance() {
    if (!chanceLabel) return;
    float ch = checkChance(activeHandIndexLayout + 1);
    if (std::isnan(ch) || std::isinf(ch)) ch = 0.0f;
    int percent = static_cast<int>(ch * 100);
    chanceLabel->setText("Шанс взять без перебора: " + QString::number(percent) + "%");
}

void updateAnalys() {
    if (!gamesLabel || !cardsLabel || !winsLabel) return;

    gamesLabel->setText("Сыграно игр: " + QString::number(playedGames));

    cardsLabel->setText("Взято карт: " + QString::number(takedCards) +
                        ", Сыграно карт: " + QString::number(playedCards));

    QString winsText = "Победных рук: " + QString::number(winnedHands);
    if (playedHands > 0) {
        double winRate = (double)winnedHands / playedHands * 100.0;
        winsText += " (" + QString::number(winRate, 'f', 1) + "%)";
    }

    winsText += "\nСыграно рук: " + QString::number(playedHands);
    winsLabel->setText(winsText);
}

void checkAnalys() {
    int currentTakedCards = 0;
    for (int i = 0; i < allPlayerHandsLayouts.size(); i++) {
        currentTakedCards += allPlayerHandsLayouts[i]->count();
    }
    int dealerCards = windowUI->dealer->layout()->count();
    int currentPlayedCards = currentTakedCards + dealerCards - 1;
    int currentPlayedHands = allPlayerHandsLayouts.size();

    addGame(currentPlayedCards, currentTakedCards, currentPlayedHands);

    int dealerScore = checkScore(0);
    for (int i = 0; i < allPlayerHandsLayouts.size(); ++i) {
        int playerScore = checkScore(i + 1);
        if (playerScore > 21) continue;
        if (dealerScore > 21 || playerScore >= dealerScore) {
            ++winnedHands;
        }
    }

    updateAnalys();
}

void startGame(){
    windowUI->add->setEnabled(1);
    windowUI->stay->setEnabled(1);
    windowUI->nextGame->setDisabled(1);
    activeHandIndexLayout = 0;
    addHand();
    layoutToAdd = allPlayerHandsLayouts[activeHandIndexLayout];
    dealerStartUI();
    add();
    add();
    allPlayerHandsLayouts[0]->parentWidget()->setStyleSheet("QWidget{"
                                                            "border: 3px dashed #FF1493;"
                                                            "border-radius: 10px;"
                                                            "background-color: #FFF0F5;"
                                                            "}");
    playerScoreLabels[0]->setStyleSheet("font-size: 14px; color: black; font-weight: bold;");
}

void dealerStartUI(){
    if (!dealerScoreLabel) {
        dealerScoreLabel = new QLabel("Счёт: ?");
        dealerScoreLabel->setStyleSheet("font-size: 14px; color: white; font-weight: bold;");
        windowUI->dealer->addWidget(dealerScoreLabel);
    }

    pair<string, int> newCard = dealerStart();
    QLabel* newCardLabel = new QLabel;
    QString text = QString::fromStdString(newCard.first);
    styleCardLabel(newCardLabel, text);
    windowUI->dealer->addWidget(newCardLabel);

    newCardLabel = new QLabel;
    styleCardLabel(newCardLabel, "");
    windowUI->dealer->addWidget(newCardLabel);
    windowUI->dealer->update();
}

void dealerEndUI(){
    QLayoutItem* labelToDelete = windowUI->dealer->takeAt(windowUI->dealer->count() - 1);
    windowUI->dealer->removeItem(labelToDelete);
    delete labelToDelete->widget();
    delete labelToDelete;

    vector<pair<string, int>> dealerCards = dealerTurn();

    int dealerScore = checkScore(0);
    if (dealerScoreLabel)
        dealerScoreLabel->setText("Счёт: " + QString::number(dealerScore));
    dealerScoreLabel->setStyleSheet("font-size: 14px; color: white; font-weight: bold;");

    windowUI->add->setDisabled(1);
    windowUI->stay->setDisabled(1);
    windowUI->nextGame->setEnabled(1);

    for(int i = 1; i < dealerCards.size(); i++){
        QLabel* newCardLabel = new QLabel;
        QString text = QString::fromStdString(dealerCards[i].first);
        styleCardLabel(newCardLabel, text);
        windowUI->dealer->addWidget(newCardLabel);
    }
    windowUI->split->setDisabled(1);
    windowUI->dealer->update();
}

void add(){
    pair<string, int> newCard = getCard(activeHandIndexLayout + 1);
    QLabel* newCardLabel = new QLabel;
    QString text = QString::fromStdString(newCard.first);
    styleCardLabel(newCardLabel, text);
    layoutToAdd->addWidget(newCardLabel);
    layoutToAdd->update();

    int score = checkScore(activeHandIndexLayout + 1);
    playerScoreLabels[activeHandIndexLayout]->setText("Счёт: " + QString::number(score));

    windowUI->split->setEnabled(checkSplit());
    updateChance();
    if (checkEnd()){
        stay();
    }
}

void stay(){
    stayCard();
    activeHandIndexLayout++;
    layoutToAdd = allPlayerHandsLayouts[activeHandIndexLayout];
    windowUI->split->setEnabled(checkSplit());
    allPlayerHandsLayouts[activeHandIndexLayout - 1]->parentWidget()->setStyleSheet("");
    if (activeHandIndexLayout == allPlayerHandsLayouts.size()){
        playerScoreLabels[activeHandIndex - 2]->setStyleSheet("font-size: 14px; color: white; font-weight: bold;");
        dealerEndUI();
        checkAnalys();
    } else {
        allPlayerHandsLayouts[activeHandIndexLayout]->parentWidget()->setStyleSheet("QWidget{"
                                                                                    "border: 3px dashed #FF1493;"
                                                                                    "border-radius: 10px;"
                                                                                    "background-color: #FFF0F5;"
                                                                                    "}");
        playerScoreLabels[activeHandIndex - 1]->setStyleSheet("font-size: 14px; color: black; font-weight: bold;");
        playerScoreLabels[activeHandIndex - 2]->setStyleSheet("font-size: 14px; color: white; font-weight: bold;");
        updateChance();
    }
}

void split(){
    splitCards();
    addHand();
    QLayoutItem* labelToSplit = allPlayerHandsLayouts[activeHandIndexLayout]->takeAt(allPlayerHandsLayouts[activeHandIndexLayout]->count() - 1);
    allPlayerHandsLayouts[activeHandIndexLayout]->removeItem(labelToSplit);
    allPlayerHandsLayouts[activeHandIndexLayout]->update();
    allPlayerHandsLayouts[allPlayerHandsLayouts.size() - 1]->addWidget(labelToSplit->widget());
    allPlayerHandsLayouts[allPlayerHandsLayouts.size() - 1]->update();
    windowUI->split->setDisabled(1);
    updateChance();
    int score = checkScore(activeHandIndexLayout + 1);
    playerScoreLabels[activeHandIndexLayout]->setText("Счёт: " + QString::number(score));
    score = checkScore(allPlayerHandsLayouts.size());
    playerScoreLabels[allPlayerHandsLayouts.size() - 1]->setText("Счёт: " + QString::number(score));
}

void newGame(){
    clearLayouts();
    if (endedPack){
        createGame();
    } else {
        playGame();
    }
    startGame();
}

void gameWindow::endGame() {
    QDialog* dialog = new QDialog(this);
    dialog->setWindowTitle("Завершение игры");
    dialog->setFixedSize(400, 150);

    QVBoxLayout* layout = new QVBoxLayout;
    dialog->setLayout(layout);

    QLabel* label = new QLabel("Вы действительно хотите завершить игру?");
    layout->addWidget(label);

    QPushButton* exitButton = new QPushButton("Выйти");
    QPushButton* resetButton = new QPushButton("Сбросить статистику");

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(resetButton);
    buttonLayout->addWidget(exitButton);

    layout->addLayout(buttonLayout);

    connect(exitButton, &QPushButton::clicked, this, []() {
        QApplication::quit();
    });

    connect(resetButton, &QPushButton::clicked, this, [=]() {
        playedGames = 0;
        takedCards = 0;
        playedCards = 0;
        winnedHands = 0;
        playedHands = 0;
        updateAnalys();
        dialog->close();
        clearLayouts();
        createGame();
        startGame();
    });
    label->setStyleSheet("color: white; font-size: 16px; qproperty-alignment: AlignCenter;");
    exitButton->setStyleSheet(       R"( background-color: #444;
                              color: white;
                              padding: 8px;
                              border-radius: 6px;
                              font-weight: bold;)");
    resetButton->setStyleSheet(R"( background-color: #444;
                              color: white;
                              padding: 8px;
                              border-radius: 6px;
                              font-weight: bold;)");
    dialog->setStyleSheet("background-color: #222;");
    dialog->exec();
}

void addHand(){
    QWidget* newHandWidget = new QWidget;
    QVBoxLayout* vLayout = new QVBoxLayout;
    QLabel* scoreLabel = new QLabel("Счёт: 0");
    scoreLabel->setStyleSheet("font-size: 14px; color: white; font-weight: bold;");
    QHBoxLayout* cardsLayout = new QHBoxLayout;

    vLayout->addWidget(scoreLabel);
    vLayout->addLayout(cardsLayout);
    newHandWidget->setLayout(vLayout);

    windowUI->playerHands->addWidget(newHandWidget);
    allPlayerHandsLayouts.push_back(cardsLayout);
    playerScoreLabels.push_back(scoreLabel);

    windowUI->playerHands->update();
}

void clearLayout(QLayout *layout) {
    if (layout == NULL)
        return;
    QLayoutItem *item;
    while((item = layout->takeAt(0))) {
        if (item->layout()) {
            clearLayout(item->layout());
            delete item->layout();
        }
        if (item->widget()) {
            delete item->widget();
        }
        delete item;
    }
}

void clearLayouts(){
    clearLayout(windowUI->playerHands);
    clearLayout(windowUI->dealer);
    allPlayerHandsLayouts.clear();
    playerScoreLabels.clear();
    dealerScoreLabel = nullptr;
}

void styleCardLabel(QLabel* label, QString text) {
    label->setText(text);
    label->setAlignment(Qt::AlignCenter);
    label->setFixedSize(80, 120);
    label->setStyleSheet(
        "QLabel {"
        "  border: 2px solid #000000;"
        "  border-radius: 8px;"
        "  background-color: white;"
        "  font-size: 20px;"
        "  font-weight: bold;"
        "  color: black;"
        "}"
        );
    label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

gameWindow::~gameWindow()
{
    delete ui;
}
