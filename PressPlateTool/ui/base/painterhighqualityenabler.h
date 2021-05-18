#ifndef PAINTERHIGHQUALITYENABLER_H
#define PAINTERHIGHQUALITYENABLER_H

#include <QPainter>

class PainterHighQualityEnabler
{
public:
    explicit PainterHighQualityEnabler(QPainter& p);
    ~PainterHighQualityEnabler();

    PainterHighQualityEnabler(const PainterHighQualityEnabler&) = delete;
    PainterHighQualityEnabler& operator=(const PainterHighQualityEnabler&) = delete;
private:
    QPainter& m_painter;
    QPainter::RenderHints m_hints;
};

#endif // PAINTERHIGHQUALITYENABLER_H
