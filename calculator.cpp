#include "calculator.h"
#include "ui_calculator.h"
#include <QRegularExpression>
#include <QKeyEvent>

double calcVal = 0.0;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;


Calculator::Calculator(QWidget *parent) :
    QMainWindow(parent)
    , ui(new Ui::Calculator)
{
    ui->setupUi(this);

    ui->Display->setText(QString::number(calcVal));
    QPushButton *numButtons[10];
    for(int i = 0; i < 10; i++){
        QString butName = "Button" + QString::number(i);
        numButtons[i] = Calculator::findChild<QPushButton *>(butName);
        connect(numButtons[i], SIGNAL(released()), this,
                SLOT(numPressed()));
    }

    connect(ui->Add, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Subtract, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Multiply, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Divide, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));

    connect(ui->Equals, SIGNAL(released()), this,
            SLOT(EqualButtonPressed()));

    connect(ui->ChangeState, SIGNAL(released()), this,
            SLOT(ChangeNumberSign()));

    connect(ui->Clear, SIGNAL(released()), this,
            SLOT(clearDisplay()));

}

Calculator::~Calculator()
{
    delete ui;
}

void Calculator::numPressed(){
    QPushButton *button = (QPushButton *)sender();
    QString butVal =button->text();
    QString displayVal = ui->Display->text();
    if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
        ui->Display->setText(butVal);
    } else {
        QString newVal = displayVal + butVal;
        double dblNewVal = newVal.toDouble();
        ui->Display->setText(QString::number(dblNewVal, 'g', 16));
    }
}




void Calculator::MathButtonPressed(){

    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
        divTrigger = true;
    } else if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
        multTrigger = true;
    } else if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
        addTrigger = true;
    } else {
        subTrigger = true;
    }
    ui->Display->setText("");

}
void Calculator::EqualButtonPressed(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();
    if(addTrigger || subTrigger || multTrigger || divTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
        } else if(subTrigger){
            solution = calcVal - dblDisplayVal;
        } else if(multTrigger){
            solution = calcVal * dblDisplayVal;
        } else{
            solution = calcVal / dblDisplayVal;
        }

    }
    ui->Display->setText(QString::number(solution));
}
void Calculator::ChangeNumberSign(){

    QString displayVal = ui->Display->text();
    QRegularExpression reg("[-]?[0-9.]*");
    if(reg.match(displayVal).hasMatch()){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }




    //return reg.match(displayVal).hasMatch();
}
void Calculator::clearDisplay(){

    double dblDisplayVal = 0.0;
    //QString displayVal = ui->Display->text();
    ui->Display->setText(QString::number(dblDisplayVal));
}
void Calculator::keyReleaseEvent(QKeyEvent *keyPressed){
    // Checks the Keyboard input of numbers
    if(keyPressed->key() == Qt::Key_0){
        double key = 0;
        ui->Display->setText(QString::number(key));
    }
    if(keyPressed->key() == Qt::Key_1){
        QString key = "1";
        QString displayVal = ui->Display->text();
        if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
            ui->Display->setText(key);
        } else {
            QString newVal = displayVal + key;
            double dblNewVal = newVal.toDouble();
            ui->Display->setText(QString::number(dblNewVal, 'g', 16));
        }
    }
    if(keyPressed->key() == Qt::Key_2){
        double key = 2;
        ui->Display->setText(QString::number(key));
    }
    if(keyPressed->key() == Qt::Key_3){
        double key = 3;
        ui->Display->setText(QString::number(key));
    }
    if(keyPressed->key() == Qt::Key_4){
        double key = 4;
        ui->Display->setText(QString::number(key));
    }
    if(keyPressed->key() == Qt::Key_5){
        double key = 5;
        ui->Display->setText(QString::number(key));
    }
    if(keyPressed->key() == Qt::Key_6){
        double key = 6;
        ui->Display->setText(QString::number(key));
    }
    if(keyPressed->key() == Qt::Key_7){
        double key = 7;
        ui->Display->setText(QString::number(key));
    }
    if(keyPressed->key() == Qt::Key_8){
        double key = 8;
        ui->Display->setText(QString::number(key));
    }
    if(keyPressed->key() == Qt::Key_9){
        double key = 9;
        ui->Display->setText(QString::number(key));
    }
    //Checks the Keyboard input of operators



}

