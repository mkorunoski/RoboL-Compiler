#include "envparser.h"

#include <QString>
#include <QFile>
#include <QTextStream>

#include "data.h"
#include "coin.h"

void ENVParser::parse(RoboLVisualisationEngine& engine, QString applicationDirPath)
{    
    QString location = QString("%1/%2").arg(applicationDirPath, "okolina.env");

    QFile file(location);
    if(!file.open(QIODevice::ReadOnly))
    {
        return;
    }

    QTextStream in(&file);

    int fields;
    std::vector<Barrier> barriers;
    std::vector<Coin> coins;
    Robot robot;
    Indices robotPosition = Indices(1, 1);
    CARDINAL_DIRECTION robotDirection = NORTH;

    while(!in.atEnd())
    {        
        QString line = in.readLine();
        QStringList lineList;

        if(line.startsWith("Okolina"))
        {
            line.chop(1);
            lineList = line.split("(");
            QStringList environmentSize = lineList[1].split(",");
            fields = environmentSize[0].toInt();
        }
        if(line.startsWith("Zidovi"))
        {            
            in.readLine();
            for(line = in.readLine(); line.compare("Kraj") != 0; line = in.readLine())
            {
                line = line.trimmed();
                lineList = line.split(" ");

                DIRECTION direction;
                if(lineList[0].compare("SJ") == 0)
                    direction = VERTICAL;
                else if(lineList[0].compare("IZ") == 0)
                    direction = HORIZONTAL;

                int begin, end;
                QStringList interval = lineList[2].split("-");
                begin = interval[0].toInt();
                end = interval[1].toInt();

                barriers.insert(barriers.end(), Barrier(direction, lineList[1].toInt(), begin, end));
            }
        }
        if(line.startsWith("Zetoni"))
        {
            in.readLine();
            for(line = in.readLine(); line.compare("Kraj") != 0; line = in.readLine())
            {
                line = line.trimmed();
                line = line.mid(1);
                line.chop(1);
                lineList = line.split(",");
                coins.insert(coins.end(), Coin(Indices(lineList[0].toInt(), lineList[1].toInt())));
            };
        }
        if(line.startsWith("Robot"))
        {
            line.chop(1);
            lineList = line.split(" ");
            QStringList robotData = lineList[1].split("(");

            CARDINAL_DIRECTION direction;
            if(robotData[0].compare("S") == 0)
                direction = NORTH;
            else if(robotData[0].compare("I") == 0)
                direction = EAST;
            else if(robotData[0].compare("J") == 0)
                direction = SOUTH;
            else if(robotData[0].compare("Z") == 0)
                direction = WEST;
            robotDirection = direction;

            QStringList indices = robotData[1].split(",");
            robotPosition = Indices(indices[0].toInt(), indices[1].toInt());
        }
    }

    file.close();

    engine.setGrid(fields);
    robot = Robot(robotPosition, robotDirection, 0);
    engine.setRobot(robot);
    engine.setCoins(coins);
    engine.setBarriers(barriers);
}
