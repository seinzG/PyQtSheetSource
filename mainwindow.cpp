#include "mainwindow.h"
#include "./ui_mainwindow.h"

// //TODO: start new mainwindow ===> load googleAPI and get Author information
// QString MainWindow::getAuthor() {

// }
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //TODO
    //1. create token
    this->createToken();

    //2. load sheet owners
    QStringList slOwners = this->getOwners();
    ui->comboBox->addItems(slOwners);
    QStringList slSheets = this->getSheets();
    ui->comboBox_2->addItems(slSheets);
    //3. create test_id
    QString testID = this->createTestID();
    ui->textEdit_3->setText(testID);
    /*-----------------------------------------------------------------------
    //4. Buttons handler
    */
    //5. Build array string to send to Python
    QObject::connect(ui->pushButton_2, &QPushButton::pressed, this, &MainWindow::writeRequest);
    QObject::connect(ui->pushButton, &QPushButton::pressed, this, &MainWindow::exitSlot);

    QStringList ValidTCs = {"Yes", "No"};
    ui->comboBox_3->addItems(ValidTCs);
    QStringList Automation = {"Not yet", "Can", "Can not", "Done", "Delete"};
    ui->comboBox_4->addItems(Automation);
    QStringList Type = {"Update", "New"};
    ui->comboBox_7->addItems(Type);
    QDateTime date = QDateTime::currentDateTime();
    ui->dateEdit->setDateTime(date);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::args = "";

QString MainWindow::callScript(QString scriptName) {
    QProcess process;
    process.setProcessChannelMode(QProcess::MergedChannels);
    QString exe = "python3 " + scriptName;
    process.start(exe);
    process.waitForFinished(-1);
    QString output(process.readAllStandardOutput());
    qDebug() << output << endl;
    return output;
}

QString MainWindow::createToken() {
    //TODO call createToken script and store file in correct place
    return callScript("createToken.py");
}

QStringList MainWindow::getOwners() {
    //TODO: call getOwners script and return authors name
    return parseOwners(callScript("getOwners.py"));
}

QStringList MainWindow::parseOwners(QString strOwners) {
    qsizetype length = strOwners.length();
    QStringList result = strOwners.mid(1,length-2).split("] [");

    return result;
}

QStringList MainWindow::getSheets() {
    //TODO: call getOwners script and return authors name
    QString scriptResult = callScript("getSheets.py");
    qsizetype length = scriptResult.length();
    QStringList result = scriptResult.left(length-1).split("\n");
    return result;
}

QString MainWindow::createTestID() {
    QString scriptResult = callScript("getTestCaseID.py DRC");
    qsizetype length = scriptResult.length();
    QStringList result = callScript("getTestCaseID.py DRC").left(length-2).split("] [");
    QString last = result.last();
    return last;
}

QString MainWindow::writeRequest() {
    //this->args = "\"" + ui->comboBox_2->currentText()+ "\" " +ui->textEdit_3->toPlainText() + " Functionality " + ui->textEdit_4->toPlainText() + " " + ui->textEdit_5->toPlainText() + " " + ui->textEdit_6->toPlainText() + " Valid Automation Issue Note";
    this->args = "";
    this->args += "\"1" + ui->comboBox_2->currentText() + "\" ";
    this->args += "\"2" + ui->textEdit_3->toPlainText() + "\" ";
    this->args += "\"3" + ui->textEdit_9->toPlainText() + "\" ";
    this->args += "\"4" + ui->textEdit_4->toPlainText() + "\" ";
    this->args += "\"5" + ui->textEdit_5->toPlainText() + "\" ";
    this->args += "\"6" + ui->textEdit_6->toPlainText() + "\" ";
    this->args += "\"7" + ui->comboBox_3->currentText() + "\" ";
    this->args += "\"8" + ui->comboBox_4->currentText() + "\" ";
    this->args += "\"9" + ui->textEdit_7->toPlainText() + "\" ";
    this->args += "\"10" + ui->textEdit_8->toPlainText() + "\" ";
    qDebug() << args << endl;
    QString result = callScript("write.py " + args);

    QString his_args = " ";
    his_args += "\"1" + ui->comboBox_2->currentText() + "\" ";
    his_args += "\"2" + ui->textEdit_9->toPlainText() + "\" ";
    his_args += "\"3" + ui->textEdit_7->toPlainText() + "\" ";
    his_args += "\"4" + ui->textEdit_3->toPlainText() + "\" ";
    his_args += "\"5" + ui->comboBox_7->currentText() + "\" ";
    his_args += "\"6" + ui->dateEdit->text() + "\" ";
    his_args += "\"7" + ui->comboBox->currentText() + "\" ";
    //his_args += review
    //his_args += comment
    qDebug() << his_args << endl;
    QString result_2 = callScript("UpdateHistory.py" + his_args);
    return result;
}

void MainWindow::exitSlot() {
    this->close();
}
