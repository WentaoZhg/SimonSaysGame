#ifndef MODEL_H
#define MODEL_H

#include <QObject>
#include <QTimer>
#include <QFile>
#include <QStringListModel>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QCoreApplication>

//@brief The model the game, communicates with main window on changes
class Model : public QObject
{
    Q_OBJECT
public:
    //@brief the object constructor
    explicit Model(QObject *parent = nullptr);

public slots:
    //@brief handles starting new game
    void startGame();

    //@brief handles when the red button is clicked
    void onRedButtonClicked();

    //@brief handles when the blue button is clicked
    void onBlueButtonClicked();

    //@brief sets the leaderboard
    void setLeaderboard();

    //@brief gets the leaderboard
    void getLeaderboard();

signals:
    //@brief starts the game
    void gameStarted();

    //@brief displays the blue color
    //@param displayDuation how long to show the color
    void blueColor(int displayDuation);

    //@brief displays the red color
    //@param displayDuation how long to show the color
    void redColor(int displayDuation);

    //@brief disables player buttons to prevent presses while order is being displayed
    void disablePlayerButtons();

    //@brief tells UI to show gameover screen
    void gameOverScreen();

    //@brief re enables player buttons
    void enablePlayerButtons();

    //@brief updates progess bar
    //@param progress the curent progress value
    void updateProgressBar(double progress);

    //@brief gets the current score
    //@param score the users current score
    void scoreStatus(int score);

    //@brief gets leaderboard info
    //@param leaderBoardModel Leaderboard info
    void leaderBoardInfo(QStringList leaderBoardModel);

    //@brief fetches the player name
    QString getPlayerName();

private:
    // helper method for fetching leaderboard
    QStringList fetchLeaderBoard();

    // leaderboard file
    QFile leaderboard;

    //@brief the generated computer order
    QVector<int> savedOrder;

    //@brief which button user inputed
    QVector<int> userInput;

    //@brief the current user position
    int index;

    // the user score
    int userScore;

    // progress percent
    double progress;

    //@brief compares the user input and saved order
    void compareInputs();

    //@brief handles displaying the saved order color combination
    void showColorOrder();
};

#endif // MODEL_H
