#include "painterhighqualityenabler.h"


PainterHighQualityEnabler::PainterHighQualityEnabler(QPainter &p)
    : m_painter(p)
{
    static QPainter::RenderHints hintAttrs[] = {
        QPainter::Antialiasing,
        QPainter::SmoothPixmapTransform,
        QPainter::TextAntialiasing
    };

    const auto nowHints = m_painter.renderHints();
    for (const auto hint : hintAttrs) {
        if (!(nowHints & hint)) {
            m_hints |= hint;
        }
    }

    if (m_hints) {
        m_painter.setRenderHints(m_hints);
    }
}

PainterHighQualityEnabler::~PainterHighQualityEnabler()
{
    if (m_hints) {
        m_painter.setRenderHints(m_hints, false);
    }
}
