#ifndef THEME_H
#define THEME_H

#include <QHash>
#include "style.h"

namespace Ui {

class Theme
{
public:
    ~Theme();
    Theme(const Theme& other) = delete ;
    Theme& operator=(const Theme& other) = delete;
    static Theme* instance();

    QColor rgba(int red, int green, int blue, qreal alpha);


    QColor color(const QString& name);
    void setColor(const QString& name, const QColor& color);
    void setColor(const QString& name, Ui::Color color);

    QColor defaultColor();
    QColor primaryColor();
    QColor disabledColor();
    QColor textColor();
private:
    Theme();
    void initColorPalette();
    QHash<QString, QColor> m_colorSheet;
};
}  // namespace Ui


#endif // THEME_H
