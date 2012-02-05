// Mathy Vanhoef
#ifndef QGRAPHIICSFOTOITEM_H_
#define QGRAPHIICSFOTOITEM_H_

#include <QtGui/QGraphicsItem>
#include "IGraphicsComp.h"
#include "foto.h"

class QGraphicsPixmapItem;
class QGraphicsTextItem;
class QPainter;
class QStyleOptionGraphicsItem;

/**
 *  Voorstelling van de Foto component op een QGraphicsScene.
 */
class QGraphicsFotoComp : public QGraphicsItem, public IGraphicsComp
{
public:
	QGraphicsFotoComp(Foto *foto, QGraphicsItem *parent = 0);
	void setBeschrijving(const QString &beschr);
	void setFoto(const QString &path);
	void SetPunt(const QPoint &punt);
	void SetPunt(const QPointF &punt);
	void SetSize(const QSize &size);
	void SetFont(const QFont &font);
	/*virtual*/ bool openEditDialog();
	/*virtual*/ bool compare(const Component *comp) const { return m_pFotoIntern == comp; }
	/*virtual*/ Component * getComponent() const { return m_pFotoIntern; }


protected:
	/**
	 *  Berekent de rechthoek rondom heel het component
	 */
	/*virtual*/ QRectF boundingRect() const;
	/*virtual*/ void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
	/*virtual*/ void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
	/*virtual*/ void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


private:
	/**
	 *  Plaats tussen de foto en de beschrijving van de foto
	 */
	static const int SPACE;
	Foto *m_pFotoIntern;
	QGraphicsPixmapItem *m_pFoto;
	QGraphicsTextItem *m_pBeschr;
	/**
	 *  Veranderd de locatie van de beschrijving gebaseerd op de grote van de foto en de tekst. Hierdoor
	 *  kan men zorden dat de tekst altijd mooi in het midden staat.
	 */
	void updateBeschrijvingPos();
};

#endif // QGRAPHIICSFOTOITEM_H_