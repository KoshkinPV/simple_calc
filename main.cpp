#include <QtWidgets>
#include <iostream>
#include "calc.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    Calculator calc;
    calc.setWindowTitle("Calculator");
    calc.resize(230, 200);

    calc.show();

    return a.exec();
}
