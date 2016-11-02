#ifndef ROBOL_VISUALISATION_ENGINE
#define ROBOL_VISUALISATION_ENGINE

#include <QObject>
#include <QQueue>
#include <vector>

#include <QTextEdit>
#include <QLabel>
#include <QGLWidget>
#include "data.h"
#include "robot.h"
#include "coin.h"
#include "barrier.h"
#include "tiles.h"

class RoboLVisualisationEngine : public QObject
{    
    Q_OBJECT

public:
    RoboLVisualisationEngine(QGLWidget *context);

    void draw();

    void setMoves(QQueue<COMMANDS> q);
    void setTeErrorsAndWarning(QTextEdit *teErrorsAndWarnings) { this->teErrorsAndWarnings = teErrorsAndWarnings; }
    void setLblTakenCoins(QLabel *lblTakenCoins) { this->lblTakenCoins = lblTakenCoins; }

    void loadEnvironment();    

    void setGrid(int fields);
    void setRobot(Robot& robot) { this->robot = robot; }
    void setCoins(std::vector<Coin>& positions);
    void setBarriers(std::vector<Barrier>& barriers);

    bool isEnvironmentLoaded() { return environmentLoaded; }

public slots:
    void animate();

private:
    QGLWidget *context;
    QTextEdit *teErrorsAndWarnings;
    QLabel *lblTakenCoins;

    QQueue<COMMANDS> moves;

    Tiles tiles;
    Robot robot;
    std::vector<Coin> coins;
    std::vector<Barrier> barriers;

    bool environmentLoaded;
};

#endif
