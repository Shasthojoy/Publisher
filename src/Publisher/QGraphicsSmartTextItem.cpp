#include <assert.h>
#include <QtGui/QGraphicsSceneMouseEvent>
#include <QtGui/QCursor>
#include "QGraphicsSmartTextItem.h"

#include "Component.h"

QGraphicsSmartTextItem::QGraphicsSmartTextItem(Component *comp, QGraphicsItem *parent /*= 0*/)
	 : QGraphicsTextItem(parent), m_pCompIntern(comp), m_resizing(false)
{
	assert(comp != NULL);

	setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable);

	// Stel waarden in gebaseerd op interne gegevens
	setTextWidth(m_pCompIntern->GetSize().width());
	setPos(m_pCompIntern->GetPunt());
	setFont(comp->GetFont());
}

void QGraphicsSmartTextItem::SetPunt(const QPoint &punt)
{
	m_pCompIntern->SetPunt(punt);
	setPos(punt);
}

void QGraphicsSmartTextItem::SetPunt(const QPointF &punt)
{
	m_pCompIntern->SetPunt(punt.toPoint());
	setPos(punt);
}

void QGraphicsSmartTextItem::SetSize(const QSize &size)
{
	m_pCompIntern->SetSize(QSize(size.width(), boundingRect().height()));
	setTextWidth(size.width());
}

void QGraphicsSmartTextItem::SetSize(qreal width)
{
	m_pCompIntern->SetSize(QSize(width, boundingRect().height()));
	setTextWidth(width);
}

void QGraphicsSmartTextItem::SetFont(const QFont &font)
{
	m_pCompIntern->SetFont(font);
	setFont(font);
}

/*virtual*/ void QGraphicsSmartTextItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	if(isBottomRight(event->pos()))
	{
		// If clicked in the corner, resize
		m_resizing = true;
	}

	QGraphicsTextItem::mousePressEvent(event);
}

/*virtual*/ void QGraphicsSmartTextItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	if(m_resizing)
	{
		setTextWidth(event->pos().rx());
	}
	else
	{
		QGraphicsTextItem::mouseMoveEvent(event);
	}
}

/*virtual*/ void QGraphicsSmartTextItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	SetPunt(this->pos());
	SetSize(QSize(this->boundingRect().width(), this->boundingRect().height()));

	// Muis is losgelaten, we kunnen dus onmogenlijk nog aan het resizen zijn ;)
	m_resizing = false;

	QGraphicsTextItem::mouseReleaseEvent(event);
}

/*virtual*/ void QGraphicsSmartTextItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *)
{
	openEditDialog();
}

/*virtual*/ void QGraphicsSmartTextItem::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
	handleResizeCursor(event);
}

/*virtual*/ void QGraphicsSmartTextItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
	handleResizeCursor(event);
}

/*virtual*/ void QGraphicsSmartTextItem::hoverLeaveEvent(QGraphicsSceneHoverEvent *)
{
	setCursor(QCursor(Qt::ArrowCursor));
}

bool QGraphicsSmartTextItem::isBottomRight(const QPointF &pos) const
{
	return (this->boundingRect().bottomRight() - pos).toPoint().manhattanLength() < 10;
}

void QGraphicsSmartTextItem::handleResizeCursor(const QGraphicsSceneHoverEvent *event)
{
	if(isBottomRight(event->pos()))
	{
		setCursor(QCursor(Qt::SizeFDiagCursor));
	}
	else
	{
		setCursor(QCursor(Qt::ArrowCursor));
	}
}