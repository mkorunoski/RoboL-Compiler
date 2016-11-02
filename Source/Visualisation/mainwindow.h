#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <QProcess>
#include "data.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    static void enableButtons() { s_buttonsEnabled = true; }
    void writeToFile(QString path, QString text);
    QString readFromFile(QString path);
    QQueue<COMMANDS> parseCommandsOutputFile(QString path);

    ~MainWindow();

private slots:
    void on_actionCompile_triggered();
    void on_actionReloadEnvironment_triggered();        

private:
    Ui::MainWindow *ui;
    QProcess *compiler;
    static bool s_buttonsEnabled;
};

#endif // MAIN_WINDOW_H
