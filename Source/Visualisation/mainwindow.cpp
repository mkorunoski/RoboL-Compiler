#include "mainwindow.h"
#include "ui_mainwindow.h"

bool MainWindow::s_buttonsEnabled = true;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->wGLWidget->getEngine()->setTeErrorsAndWarning(ui->teErrorsAndWarnings);
    ui->wGLWidget->getEngine()->setLblTakenCoins(ui->lblTakenCoins);
    ui->teErrorsAndWarnings->setReadOnly(true);
    ui->teRimal->setReadOnly(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCompile_triggered()
{    
    const QString compilerFolder      = QCoreApplication::applicationDirPath() + "/compiler/";
    const QString commandsOutputPath  = compilerFolder + "commandsOutput.txt";
    const QString errorOutputPath     = compilerFolder + "errorOutput.txt";
    const QString inputPath           = compilerFolder + "input.txt";
    const QString rimalOutputPath     = compilerFolder + "rimalOutput.txt";

    ui->teErrorsAndWarnings->setText("");
    ui->teRimal->setText("");

    if(!s_buttonsEnabled)
    {
        return;
    }
    if(!ui->wGLWidget->isEnvironmentLoaded())
    {
        QMessageBox(QMessageBox::Warning, "Warning", "Environment not loaded.", QMessageBox::Ok).exec();
        return;
    }
    QString sourceCode = ui->teSourceCode->toPlainText();
    if(sourceCode.isEmpty())
    {
        QMessageBox(QMessageBox::Warning, "Warning", "Write some code first.", QMessageBox::Ok).exec();
        return;
    }

    writeToFile(inputPath, sourceCode);

    // Start the compiler.
    system(QString("cd %1 & start compiler.exe").arg(compilerFolder).toStdString().c_str());
    QThread::sleep(1);

    QString errorOutput = readFromFile(errorOutputPath);
    if(errorOutput.size() != 0)
    {
        ui->teErrorsAndWarnings->setHtml("<font color=\"red\">" + errorOutput + "</font>");
        return;
    }

    s_buttonsEnabled = false;

    ui->teErrorsAndWarnings->setHtml("<font color=\"green\">No errors. Compilation successful.</font>");
    ui->teRimal->setText(readFromFile(rimalOutputPath));
    QQueue<COMMANDS> q = parseCommandsOutputFile(commandsOutputPath);
    ui->wGLWidget->animate(q);
}

void MainWindow::on_actionReloadEnvironment_triggered()
{
    if(!s_buttonsEnabled)
        return;

    ui->wGLWidget->loadEnvironment();
}

void MainWindow::writeToFile(QString path, QString text)
{
    QFile file(path);
    file.open(QIODevice::WriteOnly);
    QTextStream stream(&file);

    stream << text;

    file.close();
}

QString MainWindow::readFromFile(QString path)
{
    QString output;

    QFile file(path);
    file.open(QIODevice::ReadOnly);

    QTextStream in(&file);
    QString line;
    while(!in.atEnd())
    {
        line = in.readLine();
        output.append(line + "\n");
    }

    file.close();

    return output;
}

QQueue<COMMANDS> MainWindow::parseCommandsOutputFile(QString path)
{
    QQueue<COMMANDS> q;

    QFile file(path);
    file.open(QIODevice::ReadOnly);

    QTextStream in(&file);
    while(!in.atEnd())
    {
        QString line = in.readLine();
        if(line.compare("WALK") == 0)
        {
            q.append(WALK);
        }
        if(line.compare("TURN_LEFT") == 0)
        {
            q.append(TURN_LEFT);
        }
        if(line.compare("TURN_RIGHT") == 0)
        {
            q.append(TURN_RIGHT);
        }
        if(line.compare("TAKE") == 0)
        {
            q.append(TAKE);
        }
        if(line.compare("LEAVE") == 0)
        {
            q.append(LEAVE);
        }
    }

    file.close();

    return q;
}
