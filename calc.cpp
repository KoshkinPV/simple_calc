#include "calc.h"
#include <iostream>

Calculator::Calculator(QWidget *parrent /*= nullpte*/) : QWidget(parrent)
{
    m_num = new QLCDNumber(12);
    m_num->setSegmentStyle(QLCDNumber::Flat);
    m_num->setMinimumSize(150,50);

    QChar buttons[4][4] = {
        {'7','8','9','/'},
        {'4','5','6','*'},
        {'1','2','3','-'},
        {'0','.','=','+'},
    };

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(m_num, 0, 0, 1, 4);
    layout->addWidget(createButton("CE"), 1, 3);

    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            layout->addWidget(createButton(buttons[i][j]), i+2, j);
        }
    }
    setLayout(layout);
}

QPushButton* Calculator::createButton(const QString& str)
{
    QPushButton *but = new QPushButton(str);
    but->setMinimumSize(40,40);
    connect(but, &QPushButton::clicked,
            this, &Calculator::slotButtonClicked);
    return but;
}

void Calculator::calculate()
{
    qreal fop2 = m_stack.pop().toFloat();
    QString strOp = m_stack.pop();
    qreal fop1 = m_stack.pop().toFloat();
    qreal result = 0;

    if(strOp == "+")
    {
        result = fop1 + fop2;
    }
    if(strOp == "-")
    {
        result = fop1 - fop2;
    }
    if(strOp == "*")
    {
        result = fop1 * fop2;
    }
    if(strOp == "/")
    {
        result = fop1 / fop2;
    }
    m_num->display(result);
}


void Calculator::slotButtonClicked()
{

    QString str = ((QPushButton*) sender()) -> text(); // WTF is it???

    std::cout << str.toStdString();

    // if CE clicked - clear stack and display ""
    if(str == "CE")
    {
        m_stack.clear();
        m_display = "";
        m_num->display(0);
    }


    if(str.contains(QRegularExpression("[0-9]")))
    {
        m_display+=str;
        m_num->display(m_display.toDouble());
    }
    else if(str == ".")
    {
        m_display+=str;
        m_num->display(m_display);
    }
    else
    {
        if(m_stack.size() >= 2)
        {
            m_stack.push(QString().setNum(m_num->value()));
            calculate();
            m_stack.clear();
            m_stack.push(QString().setNum(m_num->value()));
            if(str != "=")
            {
                m_stack.push(str);
            }
        }
        else
        {
            m_stack.push(QString().setNum(m_num->value()));
            m_stack.push(str);
            m_display = "";
        }
    }

}
