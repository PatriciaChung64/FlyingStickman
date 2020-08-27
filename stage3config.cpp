#include <QFile>
#include <QString>
#include <QTextStream>
#include <QStringList>
#include <string>

#include "stage3config.h"

Stage3Config::Stage3Config(Config *config):
    stage2Config(new ExtendedConfig(*config)) {
    readConfig();
}

void Stage3Config::readConfig() {
    QFile file("stage3config.txt");

    if (file.open(QIODevice::ReadOnly)) {
        QTextStream buffer(&file);

        bool livesRead = false;
        bool baseObstalcesPerStageRead = false;
        bool stageClearRequirementIncrementRateRead = false;
        bool powerUpWidthRead = false;
        bool powerUpHeightRead = false;
        bool powerUpScoreWorthsRead = false;
        bool currencyToggleRead = false;

        while(!buffer.atEnd()) {
            QString line = buffer.readLine();
            QStringList split_line = line.split(":", QString::SkipEmptyParts);

            if (split_line.first() == "Lives") {
                lives = split_line.at(1).toInt();
                livesRead = true;
            }

            else if (split_line.first() == "baseObstaclesPerStage") {
                baseObstaclesPerStage = split_line.at(1).toInt();
                baseObstalcesPerStageRead = true;
            }

            else if (split_line.first() == "stageClearRequirementIncrementRate") {
                stageClearRequirementIncrementRate = split_line.at(1).toInt();
                stageClearRequirementIncrementRateRead = true;
            }

            else if (split_line.first() == "powerUpWidth") {
                powerUpWidth = split_line.at(1).toInt();
                powerUpWidthRead = true;
            }

            else if (split_line.first() == "powerUpHeight") {
                powerUpHeight = split_line.at(1).toInt();
                powerUpHeightRead = true;
            }

            else if (split_line.first() == "scoreWorth") {
                QStringList scores_split = split_line.at(1).split(",", QString::SkipEmptyParts);
                for (auto score: scores_split) {
                    scoreWorth.push_back(score.toInt());
                }
                powerUpScoreWorthsRead = true;
            }

            else if (split_line.first() == "currency") {
                if (split_line.at(1).toInt() == 0) {
                    currencyToggle = false;
                }
                else {
                    currencyToggle = true;
                }
                currencyToggleRead = true;
            }

            else {
               std::cerr << "Invalid parameter provided" << std::endl
                         << "Please ensure config file is of the correct format"
                         << std::endl;
            }
        }

        if (!(livesRead && baseObstalcesPerStageRead && stageClearRequirementIncrementRateRead
              && powerUpWidthRead && powerUpHeightRead && powerUpScoreWorthsRead)) {
            std::cerr << "Missing parameter" << std::endl
                      << "Please ensure config file is of the correct format"
                      << std::endl;
        }

        file.close();
    }

    else {
        std::cerr << "Stage 3 config file not found." << std::endl
                  << "Please ensure file is in the right directiory and of the right name."
                  << std::endl;
    }
}
