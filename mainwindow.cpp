#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    // Sets up initial game window values
    game = new Model(this);
    ui->setupUi(this);
    ui->redButton->setDisabled(true);
    ui->blueButton->setDisabled(true);
    ui->gameTitle->setEnabled(false);
    ui->leaderBoard->setEnabled(false);
    ui->leaderBoardTitle->setEnabled(false);
    ui->scoreText->setEnabled(false);
    ui->saveScoreBtn->setVisible(false);
    ui->gameOverLabel->setVisible(false);
    ui->nameText->setVisible(false);

    // Connect to red, blue, and start button and handles signals
    connect(game, &Model::gameStarted, this, &MainWindow::gameStart);
    connect(ui->startButton, &QPushButton::clicked, game, &Model::startGame);
    connect(ui->redButton, &QPushButton::clicked, game, &Model::onRedButtonClicked);
    connect(ui->blueButton, &QPushButton::clicked, game, &Model::onBlueButtonClicked);\

    // Updates game window buttons and window visuals
    connect(game, &Model::disablePlayerButtons, this, &MainWindow::disablePlayerButtons);
    connect(game, &Model::enablePlayerButtons, this, &MainWindow::enablePlayerButtons);
    connect(game, &Model::gameOverScreen, this, &MainWindow::showGameOverScreen);
    connect(game, &Model::updateProgressBar, this, &MainWindow::showProgressBar);
    connect(game, &Model::blueColor, this, &MainWindow::displayBlue);
    connect(game, &Model::redColor, this, &MainWindow::displayRed);
    connect(game, &Model::scoreStatus, this, &MainWindow::updateScore);
    connect(game, &Model::leaderBoardInfo, this, &MainWindow::drawLeaderBoard);
    connect(ui->nameText, &QLineEdit::returnPressed, game, &Model::setLeaderboard);
    connect(ui->saveScoreBtn, &QPushButton::clicked, game, &Model::setLeaderboard);
    connect(game, &Model::getPlayerName, this, &MainWindow::getPlayerName);

    game->getLeaderboard();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::gameStart()
{
    ui->startButton->hide();
    ui->redButton->show();
    ui->blueButton->show();
    ui->progressBar->show();
    ui->progressBar->setValue(0);
    ui->gameOverLabel->setVisible(false);
    ui->nameText->setVisible(false);
    ui->saveScoreBtn->setVisible(false);
}

void MainWindow::displayBlue(int displayDuration)
{
    ui->blueButton->setStyleSheet( QString(
        "background-color: rgb(150,150,255);"));
    QTimer::singleShot(displayDuration, this, &MainWindow::resetBlue);
}

void MainWindow::resetBlue()
{
    ui->blueButton->setStyleSheet("background-color: rgb(0,0,255);");
}

void MainWindow::displayRed(int displayDuration)
{
    ui->redButton->setStyleSheet( QString(
        "background-color: rgb(255,150,150);"));
    QTimer::singleShot(displayDuration, this, &MainWindow::resetRed);
}

void MainWindow::resetRed()
{
    ui->redButton->setStyleSheet("background-color: rgb(170,0,0);");
}

void MainWindow::disablePlayerButtons()
{
    ui->redButton->setDisabled(true);
    ui->blueButton->setDisabled(true);
}

void MainWindow::enablePlayerButtons()
{
    ui->redButton->setDisabled(false);
    ui->blueButton->setDisabled(false);
}

void MainWindow::showGameOverScreen()
{
    ui->redButton->hide();
    ui->blueButton->hide();
    ui->progressBar->hide();
    ui->startButton->show();
    ui->saveScoreBtn->setVisible(true);
    ui->gameOverLabel->setVisible(true);
    ui->nameText->setVisible(true);
}

void MainWindow::showProgressBar(int value)
{
    ui->progressBar->setValue(value);
}

void MainWindow::drawLeaderBoard(QStringList leaderBoardList)
{
    QStringListModel *model = new QStringListModel(leaderBoardList);
    ui->leaderBoard->setModel(model);
    ui->saveScoreBtn->setVisible(false);
    ui->nameText->setVisible(false);
}

void MainWindow::updateScore(int value)
{
    QString displayedScore = "Score: " + QString::number(value);
    ui->scoreText->setText(displayedScore);
}

QString MainWindow::getPlayerName()
{
    return ui->nameText->text();
}
