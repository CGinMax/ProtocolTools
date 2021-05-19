#ifndef THEME_H
#define THEME_H

#include <QHash>
#include "style.h"
#include <QVector>
namespace Ui {

class Theme
{
public:
    ~Theme();
    Theme(const Theme& other) = delete ;
    Theme& operator=(const Theme& other) = delete;
    static Theme* instance();

    static QColor rgba(int red, int green, int blue, qreal alpha);


    QColor color(const QString& name);
    QColor color(Ui::Color color);
    void setColor(const QString& name, const QColor& color);
    void setColor(const QString& name, Ui::Color color);

    QColor defaultColor();
    QColor primaryColor();
    QColor disabledColor();
    QColor textColor();

    static const QVector<QColor> palette;
private:
    Theme();
    void initColorPalette();
    bool checkOutofRange(Ui::Color color);
    QHash<QString, QColor> m_colorSheet;
};
}  // namespace Ui


#endif // THEME_H
