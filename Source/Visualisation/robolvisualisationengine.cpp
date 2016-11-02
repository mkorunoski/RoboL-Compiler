#include "robolvisualisationengine.h"

#include <QtOpenGL>
#include <GL/glu.h>
#include "envparser.h"
#include "mainwindow.h"

RoboLVisualisationEngine::RoboLVisualisationEngine(QGLWidget *context)
{
    this->context = context;

    tiles = Tiles();
    robot = Robot();
    coins = std::vector<Coin>();
    barriers = std::vector<Barrier>();

    environmentLoaded = false;
}

void RoboLVisualisationEngine::draw()
{
    tiles.draw();

    for(uint i = 0; i < coins.size(); ++i)
    {
        coins[i].draw(tiles.getGrid());
    }

    for(uint i = 0; i < barriers.size(); ++i)
    {
        barriers[i].draw(tiles.getGrid());
    }

    robot.draw(tiles.getGrid());
}

void RoboLVisualisationEngine::setMoves(QQueue<COMMANDS> q)
{
    moves = q;
}

void RoboLVisualisationEngine::loadEnvironment()
{
    ENVParser::parse(*this, QCoreApplication::applicationDirPath());
    robot.setTakenCoins(0);
    lblTakenCoins->setText(QString("Taken Coins: %1").arg(robot.getTakenCoins()));
    environmentLoaded = true;
    context->repaint();
}

void RoboLVisualisationEngine::setGrid(int fields)
{
    tiles.setGrid(fields);

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glLoadIdentity();
    int f = fields % 2 != 0 ? (fields + 1) : fields;
    gluOrtho2D(-f * 0.5, f * 0.5, -f * 0.5, f * 0.5);
    glPushMatrix();
}

void RoboLVisualisationEngine::setCoins(std::vector<Coin>& coins)
{    
    this->coins = coins;
}

void RoboLVisualisationEngine::setBarriers(std::vector<Barrier>& barriers)
{
    this->barriers = barriers;
}

void RoboLVisualisationEngine::animate()
{
    if(!environmentLoaded || moves.isEmpty())
    {
        MainWindow::enableButtons();
        return;
    }
    QString res;
    switch (moves.dequeue())
    {
    case WALK:
        res = robot.walk(tiles.getGrid(), barriers);
        if(!res.isEmpty())
            teErrorsAndWarnings->setHtml(
                        teErrorsAndWarnings->toHtml()
                        .append("<font color=\"red\">" + res + "</font>"));
        QTimer::singleShot(500, this, SLOT(animate()));
        break;
    case TURN_LEFT:
        robot.turnLeft();
        QTimer::singleShot(0, this, SLOT(animate()));
        break;
    case TURN_RIGHT:
        robot.turnRight();
        QTimer::singleShot(0, this, SLOT(animate()));
        break;
    case TAKE:
        res = robot.take(coins);
        if(!res.isEmpty())
            teErrorsAndWarnings->setHtml(
                        teErrorsAndWarnings->toHtml()
                        .append("<font color=\"red\">" + res + "</font>"));
        this->lblTakenCoins->setText(QString("Taken Coins: %1").arg(robot.getTakenCoins()));
        QTimer::singleShot(0, this, SLOT(animate()));
        break;
    case LEAVE:
        res = robot.leave(coins);
        if(!res.isEmpty())
            teErrorsAndWarnings->setText(
                        teErrorsAndWarnings->toHtml().
                        append("<font color=\"red\">" + res + "</font>"));
        this->lblTakenCoins->setText(QString("Taken Coins: %1").arg(robot.getTakenCoins()));
        QTimer::singleShot(0, this, SLOT(animate()));
        break;
    }
    context->repaint();
}
