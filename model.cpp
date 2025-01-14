#include "model.h"

Model::Model(QObject *parent) : QObject(parent) {

}

void Model::startGame() {
    // Make sure saved orders are cleared
    savedOrder.clear();
    userInput.clear();
    userScore = 0;
    // Starts game, updates score, and initializes the saved pattern and displays it
    emit scoreStatus(userScore);
    savedOrder.push_back(rand() % 2);
    emit gameStarted();
    showColorOrder();
    emit enablePlayerButtons();
}

void Model::onRedButtonClicked(){
    // If player tries to input too many times, the method returns
    if (index >= savedOrder.size())
        return;

    // Disables button temporarily and gives color feedback on button push
    emit disablePlayerButtons();
    emit redColor(250);
    userInput.push_back(0);
    compareInputs();
}

void Model::onBlueButtonClicked(){
    // If player tries to input too many times, the method returns
    if (index >= savedOrder.size())
        return;

    // Disables button temporarily and gives color feedback on button push
    emit disablePlayerButtons();
    emit blueColor(250);
    userInput.push_back(1);
    compareInputs();
}

void Model::compareInputs(){
    // Index compares current user input with the matching saved order index
    if (savedOrder[index] == userInput[index]){
        index++;
        progress = ((double)(index)/(double)savedOrder.size()) * 100;
        emit updateProgressBar(progress);
        emit enablePlayerButtons();

        // If last index is reached, score and progress bar are updated, and a new value is
        // added to the game and shown to the player
        if (index == savedOrder.size())
        {
            userInput.clear();
            userScore++;
            emit scoreStatus(userScore);
            QTimer::singleShot(750, this, [this](){
                emit updateProgressBar(0);
                savedOrder.push_back(rand() % 2);
                showColorOrder();
            });
        }
    }else{
        emit disablePlayerButtons();
        emit gameOverScreen();
    }
}

void Model::showColorOrder(){
    // Buttons cannot be pushed while the pattern is being shown
    emit disablePlayerButtons();
    int counter = 0;
    int baseDelay = 1000;

    // Calculate the delay, reducing it as the game continues with a minimum of 200
    int delay = std::max(200, baseDelay - (static_cast<int>(savedOrder.size()) * 50));
    int displayDuration = delay/2;

    // For each loop iterates through saved pattern and displays it
    for(int color : savedOrder){
        QTimer::singleShot(delay * counter++, this, [this, color, displayDuration](){
            if (color == 0)
                emit redColor(displayDuration);
            else
                emit blueColor(displayDuration);
        });
    }

    // Reenables buttons
    index = 0;
    QTimer::singleShot(delay * counter, this, [this](){
        emit enablePlayerButtons();
    });
}
void Model::setLeaderboard(){
    // Saves name typed into text box to a variable and adds it to leaderboard
    QString playerName = emit getPlayerName();
    QFile leaderboard(QDir::current().absoluteFilePath("scores.txt"));
    if(leaderboard.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&leaderboard);
        out << + "\n"+ playerName+", " + QString::number(userScore);
        leaderboard.close();
    }
    QStringList leaderBoardList = fetchLeaderBoard();
    emit leaderBoardInfo(leaderBoardList);
}

void Model::getLeaderboard(){
    QStringList leaderBoardList = fetchLeaderBoard();
    emit leaderBoardInfo(leaderBoardList);
}

QStringList Model::fetchLeaderBoard(){
    QFile leaderboard(QDir::current().absoluteFilePath("scores.txt"));
    QStringList leaderBoardList;
    if(!leaderboard.exists())
    {
        if(leaderboard.open(QIODevice::WriteOnly) | QIODevice::Text)
        {
            QTextStream out(&leaderboard);
            out << "player, 10";
            leaderboard.close();
        }
    }
    if(leaderboard.open(QIODevice::ReadOnly) | QIODevice::Text)
    {
        QTextStream in(&leaderboard);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            if (parts.size() >= 2) {
                QString playerName = parts[0];
                QString score = parts[1];
                leaderBoardList.append(playerName + ": " + score);
            }
        }
        leaderboard.close();
    }

    // Sorts leaderboard by score
    std::sort(leaderBoardList.begin(), leaderBoardList.end(), [](const QString &entry1, const QString &entry2) {

        QStringList part1 = entry1.split(":");
        QStringList part2 = entry2.split(":");

        return part1[1].trimmed().toInt() > part2[1].trimmed().toInt();

    });

    return leaderBoardList;
}
