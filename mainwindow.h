#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "model.h"

//@brief The main window for the game, updates the view
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    //@brief game start handler
    void gameStart();

    //@brief display the blue button flashing
    //@param displayDuration how long to show the color
    void displayBlue(int displayDuration);

    //@brief displays the red button flashing
    //@param displayDuration how long to show the color
    void displayRed(int displayDuration);

    //@brief disable red and blue buttons
    void disablePlayerButtons();

    //@brief enables red and blue buttons
    void enablePlayerButtons();

    //@brief shows the game over screen
    void showGameOverScreen();

    //@brief shows the progress bar
    //@param value current progess bar value
    void showProgressBar(int value);

    //@brief reset red button to default color after flash
    void resetRed();

    //@brief reset blue button to default color after flash
    void resetBlue();

    //@brief draws the leaderboard
    //@param leaderBoardList the leaderboard list
    void drawLeaderBoard(QStringList leaderBoardList);

    //@brief updates score
    //@param current user score
    void updateScore(int value);

    //@brief gets playername
    QString getPlayerName();

private:
    //@brief The Game UI
    Ui::MainWindow *ui;
    //@brief The Game Model
    Model *game;
};
#endif // MAINWINDOW_H
