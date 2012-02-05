// Mathy Vanhoef
#ifndef QGRAPHICSSMARTTEXTITEM_H_
#define QGRAPHICSSMARTTEXTITEM_H_

#include <QtGui/QGraphicsTextItem>
#include "IGraphicsComp.h"

/**
 *  Basis klasse voor component die alleen tekst weergeven. Het implementeerd de basis Set en Get functies
 *  van een component, het resizen van het component en het slepen ervan. Met een eerste klik kan je het
 *  component verslepen. Met een tweede klik (als het component al geselecteerd is) kan men de tekst wijzigen.
 *
 *  Het muis icoon veranderd als de muis rechts onderaan het component is, zodat het duidelijk is voor de
 *  gebruiker dat hij dit component kan resizen.
 */
class QGraphicsSmartTextItem : public QGraphicsTextItem, public IGraphicsComp
{
	Q_OBJECT


public:
	QGraphicsSmartTextItem(Component *comp, QGraphicsItem *parent = 0);
	void SetPunt(const QPoint &punt);
	void SetPunt(const QPointF &punt);
	void SetSize(const QSize &size);
	void SetSize(const qreal width);
	void SetFont(const QFont &font);
	/*virtual*/ bool compare(const Component *comp) const { return m_pCompIntern == comp; }
	/*virtual*/ Component * getComponent() const { return m_pCompIntern; }


protected:
	Component *m_pCompIntern;
	/**
	 *  Is de gebruiker momenteel het component aan het resizen?
	 */
	bool m_resizing;
	/*virtual*/ void mousePressEvent(QGraphicsSceneMouseEvent *event);
	/*virtual*/ void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
	/*virtual*/ void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
	/*virtual*/ void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
	/*virtual*/ void hoverEnterEvent(QGraphicsSceneHoverEvent *event);
	/*virtual*/ void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
	/*virtual*/ void hoverLeaveEvent(QGraphicsSceneHoverEvent *);
	/**
	 *  Geeft true terug als het punt rechts onderaan het component is (handig voor o.a. resize!)
	 */
	bool isBottomRight(const QPointF &pos) const;
	/**
	 *  Veranderd de cursor indien deze rechts onderaan het component is naar de "resize cursor".
	 */
	void handleResizeCursor(const QGraphicsSceneHoverEvent *event);	
};

#endif // QGRAPHICSSMARTTEXTITEM_H_