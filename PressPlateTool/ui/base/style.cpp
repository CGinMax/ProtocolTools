#include "style.h"

double Ui::calcGrayLevel(int red, int green, int blue)
{
    return (0.299 * red + 0.587 * green + 0.114 * blue) / 255;
}

QColor Ui::reverseColor(double grayLevel)
{
    return grayLevel > 0.5 ? Qt::black : Qt::white;
}

QColor Ui::reverseColor(const QColor &color)
{
    return Ui::reverseColor(Ui::calcGrayLevel(color.red(), color.green(), color.blue()));
}
