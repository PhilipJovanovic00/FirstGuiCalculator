#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <QMainWindow>

//QT_BEGIN_NAMESPACE
namespace Ui { class Calculator; }
//QT_END_NAMESPACE

class Calculator : public QMainWindow
{
    Q_OBJECT

public:
    explicit Calculator(QWidget *parent = 0); //nullptr
    ~Calculator();

    void keyReleaseEvent(QKeyEvent *keyPressed);
private:
    Ui::Calculator *ui;

private slots:
    void numPressed();
    void commaPressed();
    void logPressed();
    void lnPressed();
    void piPressed();
    void ePressed();
    void MathButtonPressed();
    void sqrtPressed();
    void EqualButtonPressed();
    void ChangeNumberSign();
    void clearDisplay();
};
#endif // CALCULATOR_H
