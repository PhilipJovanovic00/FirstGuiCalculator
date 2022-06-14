#include "calculator.h"
#include "ui_calculator.h"
#include <QRegularExpression>
#include <QKeyEvent>
#include <math.h>

double calcVal = 0.0;
double piValue = 3.14159265359;
double eValue = 2.7182818284;
bool divTrigger = false;
bool multTrigger = false;
bool addTrigger = false;
bool subTrigger = false;
bool sqrtTrigger = false;
bool powTrigger = false;
bool logTrigger = false;


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
    connect(ui->Sqrt, SIGNAL(released()), this,
            SLOT(sqrtPressed()));
    connect(ui->Pow, SIGNAL(released()), this,
            SLOT(MathButtonPressed()));
    connect(ui->Comma, SIGNAL(released()), this,
            SLOT(commaPressed()));
    connect(ui->Logging, SIGNAL(released()), this,
            SLOT(logPressed()));
    connect(ui->Pi, SIGNAL(released()), this,
            SLOT(piPressed()));
    connect(ui->EulersNum, SIGNAL(released()), this,
            SLOT(ePressed()));
    connect(ui->LogNat, SIGNAL(released()), this,
            SLOT(lnPressed()));


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
        ui->Display->setText(QString::number(dblNewVal, 'g', 10));
    }
}
void Calculator::commaPressed(){
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    ui->Display->setText(ui->Display->text() + butVal);
}
void Calculator::logPressed(){
    logTrigger = true;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    double solution = log10(calcVal);
    ui->Display->setText(QString::number(solution));
}
void Calculator::lnPressed(){
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    double solution = log10(calcVal) / log10(eValue);
    ui->Display->setText(QString::number(solution));
}

void Calculator::piPressed(){
    ui->Display->setText(QString::number(piValue));

}
void Calculator::ePressed(){
    ui->Display->setText(QString::number(eValue));
}



void Calculator::MathButtonPressed(){

    divTrigger = false;
    multTrigger = false;
    addTrigger = false;
    subTrigger = false;
    sqrtTrigger = false;
    powTrigger = false;
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
    } else if(QString::compare(butVal, "-", Qt::CaseInsensitive) == 0){
        subTrigger = true;
    } else if(QString::compare(butVal, "√", Qt::CaseInsensitive) == 0){
        sqrtTrigger = true;
    } else if(QString::compare(butVal, "^", Qt::CaseInsensitive) == 0){
        powTrigger = true;
    }
    ui->Display->setText("");

}

void Calculator::sqrtPressed(){
    sqrtTrigger = false;
    QString displayVal = ui->Display->text();
    calcVal = displayVal.toDouble();
    QPushButton *button = (QPushButton *)sender();
    QString butVal = button->text();
    if(QString::compare(butVal, "√", Qt::CaseInsensitive) == 0){
            sqrtTrigger = true;
        }
    ui->Display->setText("");
    double solution = 0.0;
    if(sqrtTrigger){
        solution = sqrt(calcVal);
    }
    ui->Display->setText(QString::number(solution));
}

void Calculator::EqualButtonPressed(){
    double solution = 0.0;
    QString displayVal = ui->Display->text();
    double dblDisplayVal = displayVal.toDouble();

    if(addTrigger || subTrigger || multTrigger || divTrigger || sqrtTrigger || powTrigger || logTrigger){
        if(addTrigger){
            solution = calcVal + dblDisplayVal;
            ui->Display->setText(QString::number(solution));
        } else if(subTrigger){
            solution = calcVal - dblDisplayVal;
            ui->Display->setText(QString::number(solution));
        } else if(multTrigger){
            solution = calcVal * dblDisplayVal;
            ui->Display->setText(QString::number(solution));
        } else if(dblDisplayVal == 0){
                ui->Display->setText("Division through 0 is not possible");
        } else if(divTrigger){
            solution = calcVal / dblDisplayVal;
            ui->Display->setText(QString::number(solution));

        } else if(sqrtTrigger){
           solution = sqrt(dblDisplayVal);
           ui->Display->setText(QString::number(solution));
        } else if(powTrigger){
            solution = pow(calcVal, dblDisplayVal);
            ui->Display->setText(QString::number(solution));
        } else if(logTrigger){
            solution = dblDisplayVal;
            ui->Display->setText(QString::number(solution));
        }
    }

    //ui->Display->setText(QString::number(solution));
}


void Calculator::ChangeNumberSign(){

    QString displayVal = ui->Display->text();
    QRegularExpression reg("[-]?[0-9.]*");
    if(reg.match(displayVal).hasMatch()){
        double dblDisplayVal = displayVal.toDouble();
        double dblDisplayValSign = -1 * dblDisplayVal;
        ui->Display->setText(QString::number(dblDisplayValSign));
    }
}
void Calculator::clearDisplay(){

    double dblDisplayVal = 0.0;
    //QString displayVal = ui->Display->text();
    ui->Display->setText(QString::number(dblDisplayVal));
}

void Calculator::keyReleaseEvent(QKeyEvent *keyPressed){
    // From 0 to 9, this is called if the user inputs a number
    //on the keyboard. The value is then Displayed.
    if(keyPressed->key() == Qt::Key_0){
        QString key = "0";
        QString displayVal = ui->Display->text();
        if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
            ui->Display->setText(key);
        } else {
            QString newVal = displayVal + key;
            double dblNewVal = newVal.toDouble();
            ui->Display->setText(QString::number(dblNewVal, 'g', 16));
        }
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
        QString key = "2";
        QString displayVal = ui->Display->text();
        if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
            ui->Display->setText(key);
        } else {
            QString newVal = displayVal + key;
            double dblNewVal = newVal.toDouble();
            ui->Display->setText(QString::number(dblNewVal, 'g', 16));
        }
    }
    if(keyPressed->key() == Qt::Key_3){
        QString key = "3";
        QString displayVal = ui->Display->text();
        if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
            ui->Display->setText(key);
        } else {
            QString newVal = displayVal + key;
            double dblNewVal = newVal.toDouble();
            ui->Display->setText(QString::number(dblNewVal, 'g', 16));
        }
    }
    if(keyPressed->key() == Qt::Key_4){
        QString key = "4";
        QString displayVal = ui->Display->text();
        if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
            ui->Display->setText(key);
        } else {
            QString newVal = displayVal + key;
            double dblNewVal = newVal.toDouble();
            ui->Display->setText(QString::number(dblNewVal, 'g', 16));
        }
    }
    if(keyPressed->key() == Qt::Key_5){
        QString key = "5";
        QString displayVal = ui->Display->text();

        if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
            ui->Display->setText(key);
        } else {
            QString newVal = displayVal + key;
            double dblNewVal = newVal.toDouble();
            ui->Display->setText(QString::number(dblNewVal, 'g', 16));
        }

    }
    if(keyPressed->key() == Qt::Key_6){
        QString key = "6";
        QString displayVal = ui->Display->text();
        if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
            ui->Display->setText(key);
        } else {
            QString newVal = displayVal + key;
            double dblNewVal = newVal.toDouble();
            ui->Display->setText(QString::number(dblNewVal, 'g', 16));
            //ui->tabWidget->tab->listView->setText();
        }
    }
    if(keyPressed->key() == Qt::Key_7){
        QString key = "7";
        QString displayVal = ui->Display->text();
        if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
            ui->Display->setText(key);
        } else {
            QString newVal = displayVal + key;
            double dblNewVal = newVal.toDouble();
            ui->Display->setText(QString::number(dblNewVal, 'g', 16));
        }
    }
    if(keyPressed->key() == Qt::Key_8){
        QString key = "8";
        QString displayVal = ui->Display->text();
        if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
            ui->Display->setText(key);
        } else {
            QString newVal = displayVal + key;
            double dblNewVal = newVal.toDouble();
            ui->Display->setText(QString::number(dblNewVal, 'g', 16));
        }
    }
    if(keyPressed->key() == Qt::Key_9){
        QString key = "9";
        QString displayVal = ui->Display->text();
        if((displayVal.toDouble() == 0) || (displayVal.toDouble() == 0.0)){
            ui->Display->setText(key);
        } else {
            QString newVal = displayVal + key;
            double dblNewVal = newVal.toDouble();
            ui->Display->setText(QString::number(dblNewVal, 'g', 16));
        }
    }
    //Checks the Keyboard input of the Enter (Return) Key.
    if(keyPressed->key() == Qt::Key_Return){
        double solution = 0.0;
        QString displayVal = ui->Display->text();
        double dblDisplayVal = displayVal.toDouble();
        if(addTrigger || subTrigger || multTrigger || divTrigger || sqrtTrigger || powTrigger){
            if(addTrigger){
                solution = calcVal + dblDisplayVal;
                ui->Display->setText(QString::number(solution));
                addTrigger = false;
            } else if(subTrigger){
                solution = calcVal - dblDisplayVal;
                ui->Display->setText(QString::number(solution));
                subTrigger = false;
            } else if(multTrigger){
                solution = calcVal * dblDisplayVal;
                ui->Display->setText(QString::number(solution));
                multTrigger = false;
            } else if(divTrigger){
                if(dblDisplayVal == 0){
                ui->Display->setText("Division through 0 is not possible");
                divTrigger = false;
                } else{
                    solution = calcVal / dblDisplayVal;
                    ui->Display->setText(QString::number(solution));
                    divTrigger = false;
                }
            } else if(sqrtTrigger){
                solution = sqrt(calcVal);
                ui->Display->setText(QString::number(solution));
            } else if(powTrigger){
                solution = pow(calcVal, dblDisplayVal);
                ui->Display->setText(QString::number(solution));
            }

        }

    }
    //This Method is called when the user presses the enter key, it also calculates
    //the result and Displays it on the display
    if(keyPressed->key() == Qt::Key_Enter){
        double solution = 0.0;
        QString displayVal = ui->Display->text();
        double dblDisplayVal = displayVal.toDouble();
        if(addTrigger || subTrigger || multTrigger || divTrigger || sqrtTrigger || powTrigger){
            if(addTrigger){
                solution = calcVal + dblDisplayVal;
                ui->Display->setText(QString::number(solution));
                addTrigger = false;
            } else if(subTrigger){
                solution = calcVal - dblDisplayVal;
                ui->Display->setText(QString::number(solution));
                subTrigger = false;
            } else if(multTrigger){
                solution = calcVal * dblDisplayVal;
                ui->Display->setText(QString::number(solution));
                multTrigger = false;
            } else if(divTrigger){
                if(dblDisplayVal == 0){
                ui->Display->setText("Division through 0 is not possible");
                divTrigger = false;
                } else{
                    solution = calcVal / dblDisplayVal;
                    ui->Display->setText(QString::number(solution));
                    divTrigger = false;

                }
            } else if(sqrtTrigger){
                solution = sqrt(calcVal);
                ui->Display->setText(QString::number(solution));
            } else if(powTrigger){
                solution = pow(calcVal, dblDisplayVal);
                ui->Display->setText(QString::number(solution));
            }
        }
    }
    //Deletes the Display if the Key c is pressed
    if(keyPressed->key() == Qt::Key_C){
        double dblDisplayVal = 0.0;
        ui->Display->setText(QString::number(dblDisplayVal));
    }
    //Change the state of a number when the - Key is pressed
    if(keyPressed->key() == Qt::Key_S){
        QString displayVal = ui->Display->text();
        QRegularExpression reg("[-]?[0-9.]*");
        if(reg.match(displayVal).hasMatch()){
            double dblDisplayVal = displayVal.toDouble();
            double dblDisplayValSign = -1 * dblDisplayVal;
            ui->Display->setText(QString::number(dblDisplayValSign));
        }
    }
    //Takes the + Operator and does the Operation
    if(keyPressed->key() == Qt::Key_Plus){
        addTrigger = false;
        QString displayVal = ui->Display->text();
        calcVal = displayVal.toDouble();
        //QPushButton *button = (QPushButton *)sender();
        QString butVal = "+";
        if(QString::compare(butVal, "+", Qt::CaseInsensitive) == 0){
            addTrigger = true;
        }
        ui->Display->setText("+");
    }
    //Takes the - Operator and does the Operation
    if(keyPressed->key() == Qt::Key_Minus){
        subTrigger = false;
        QString displayVal = ui->Display->text();
        calcVal = displayVal.toDouble();
        //QPushButton *button = (QPushButton *)sender();
        QString butVal = "-";
        if(QString::compare(butVal, "-", Qt::CaseInsensitive) == 0){
            subTrigger = true;
        }
        ui->Display->setText("-");
    }
    //Takes the * Operator and does the Operation
    if(keyPressed->key() == Qt::Key_Asterisk){
        multTrigger = false;
        QString displayVal = ui->Display->text();
        calcVal = displayVal.toDouble();
        //QPushButton *button = (QPushButton *)sender();
        QString butVal = "*";
        if(QString::compare(butVal, "*", Qt::CaseInsensitive) == 0){
            multTrigger = true;
        }
        ui->Display->setText("*");
    }
    //Takes the / Operator and does the Operation
    if(keyPressed->key() == Qt::Key_Slash){
        divTrigger = false;
        QString displayVal = ui->Display->text();
        calcVal = displayVal.toDouble();
        //QPushButton *button = (QPushButton *)sender();
        QString butVal = "/";
        if(QString::compare(butVal, "/", Qt::CaseInsensitive) == 0){
            divTrigger = true;
        }
        ui->Display->setText("/");
    }

    //Takes the ^ and takes the Power of a number
    if(keyPressed->key()  == Qt::Key_AsciiCircum){
        powTrigger = true;
        QString displayVal = ui->Display->text();
        calcVal = displayVal.toDouble();
        QString butVal = "^";
        if(QString::compare(butVal, "^", Qt::CaseInsensitive) == 0){
            powTrigger = true;
        }
        ui->Display->setText("^");

    }
    if(keyPressed->key() == Qt::Key_Period){
        QString displayVal = ui->Display->text();
        calcVal = displayVal.toDouble();
        QString keyPeriod = ".";
        ui->Display->setText(ui->Display->text() + keyPeriod);
    }


    //Further implementation of user input will come soon
}

