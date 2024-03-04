#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QDebug>

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

private:
    Ui::MainWindow *ui;
    QString callScript(QString scriptName);
    QString createToken();
    QStringList getOwners();
    QStringList parseOwners(QString strOwners);
    QStringList getSheets();
    QString createTestID();
    QString writeRequest();
    QString createArgs();
    static QString args;
public slots:
    void exitSlot();
};
#endif // MAINWINDOW_H
