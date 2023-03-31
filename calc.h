#pragma once
#include <QtWidgets>

class QLCDNumber;
class QPushButton;

class Calculator : public QWidget
{
    Q_OBJECT
public:
    Calculator(QWidget *parrent = nullptr);

    QPushButton *createButton(const QString& str);

    void calculate();

public slots:
    void slotButtonClicked();

private:
    QLCDNumber *m_num;
    QStack<QString> m_stack;
    QString m_display;

};

