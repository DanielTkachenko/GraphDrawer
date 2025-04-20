#include "plotview.h"
#include "filereader.h"
#include <QPainter>
#include <QPainterPath>
#include <iostream>



PlotView::PlotView(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    m_bounds.minX = 0.0;
    m_bounds.maxX = 10e9;
    m_bounds.minY = -25.0;
    m_bounds.maxY = 0.0;

    m_points << QPointF(0, 6)
    << QPointF(2, 4)
    << QPointF(3, 8)
    << QPointF(7, 4)
    << QPointF(10, 5);
}

void PlotView::updatePlot(const QVector<QPointF> &points)
{
    m_points = points;
    update();
}

void PlotView::paint(QPainter *painter)
{
    painter->setRenderHint(QPainter::Antialiasing);

    m_size = size();


    //===Сетка координат===
    paintGraph(painter);
    // === График ===
    paintLine(painter);
}

void PlotView::paintGraph(QPainter *painter)
{
    double gridStepX = m_size.width() / 10.0;
    double gridStepY = m_size.height() / 10.0;

    QFont font = painter->font();
    font.setPointSize(9);
    painter->setFont(font);
    QFontMetrics fm(font);

    // === Заголовок графика ===
    QFont titleFont = font;
    titleFont.setPointSize(14);
    titleFont.setBold(true);
    painter->setFont(titleFont);
    QString title = "";
    painter->drawText((m_size.width() - fm.horizontalAdvance(title)) / 2, fm.height() + 5, title);

    // Вернуть обычный шрифт
    painter->setFont(font);

    // === Сетка с подписями вдоль линий ===
    QPen gridPen(Qt::lightGray, 1, Qt::DashLine);
    painter->setPen(gridPen);

    for (int i = 1; i < 10; ++i) {
        int x = i * gridStepX;
        int y = m_size.height() - i * gridStepY;

        // Вертикальные линии
        painter->drawLine(x, 0, x, m_size.height());
        painter->drawText(x + 2, m_size.height() - 4, QString::number(i)); // Подписи на вертикальных линиях снизу

        // Горизонтальные линии
        painter->drawLine(0, y, m_size.width(), y);
        painter->drawText(5, y - 4, QString::number(i)); // Подписи слева от горизонтальных линий
    }

    // === Оси ===
    painter->setPen(QPen(Qt::black, 1));
    painter->drawLine(QPointF(0, m_size.height()), QPointF(m_size.width(), m_size.height()));  // X
    painter->drawLine(QPointF(0, 0), QPointF(0, m_size.height()));                      // Y

    // === Названия осей ===
    painter->drawText(m_size.width() / 2 - 10, m_size.height() + 2 * fm.height(), "X");
    painter->save();
    painter->translate(10, m_size.height() / 2 + fm.height());
    painter->rotate(-90);
    painter->drawText(0, 0, "Y");
    painter->restore();

}

void PlotView::paintLine(QPainter *painter)
{
    if (m_points.size() < 2)
        return;

    painter->setPen(QPen(Qt::blue, 2));
    QPainterPath path;
    QPointF start = toScreenSize(m_points[0]);
    path.moveTo(start);

    for (int i = 1; i < m_points.size(); ++i) {
        QPointF p = toScreenSize(m_points[i]);
        path.lineTo(p);
    }

    painter->drawPath(path);

    // === Маркеры на точках ===
    /*painter->setBrush(Qt::red);
    for (const QPointF &p : m_points) {
        QPointF screen = toScreenSize(p);
        painter->drawEllipse(screen, 4, 4);
    }*/
}

QPointF PlotView::toScreenSize(const QPointF& point)
{
    QPointF screenPoint;
    screenPoint.setX((point.x()*1 - m_bounds.minX) / (m_bounds.maxX - m_bounds.minX) * m_size.width());
    screenPoint.setY(m_size.height() - ((point.y()*1 - m_bounds.minY)) / (m_bounds.maxY - m_bounds.minY) * m_size.height());

    return screenPoint;
}
