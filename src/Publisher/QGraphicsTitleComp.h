// Mathy Vanhoef
#ifndef QGRAPHICSTITLEITEM_H_
#define QGRAPHICSTITLEITEM_H_

#include <QtGui/QGraphicsTextItem>

#include "IGraphicsComp.h"
#include "Titel.h"

/**
 *  Voorstelling van de Titel component op een QGraphicsScene.
 */
class QGraphicsTitleComp : public QGraphicsTextItem, public IGraphicsComp
{
	Q_OBJECT


public:
	QGraphicsTitleComp(Titel *titel, QGraphicsItem *parent = 0);
	void SetPunt(const QPoint &punt);
	void SetPunt(const QPointF &punt);
	void SetSize(const QSize &size);
	void SetFont(const QFont &font);
	void SetTitel(const QString &titel);
	void SetDeelTitel(bool isDeelTitel);
	/*virtual*/ bool openEditDialog();
	/*virtual*/ bool compare(const Component *comp) const { return m_pTitelIntern == comp; }
	/*virtual*/ Component * getComponent() const { return m_pTitelIntern; }


protected:
	/*virtual*/ void QGraphicsTitleComp::mousePressEvent(QGraphicsSceneMouseEvent *event);
	/*virtual*/ void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
	/*virtual*/ void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);


private:
	Titel *m_pTitelIntern;
	/**
	 *  Update de tekst die het object weergeeft naar ofwel de deeltitel indien het een deeltitel voorstelt,
	 *  ofwel de specifieke titel die is opgegeven. Deze functie veranderd dus niet de interne component, maar
	 *  update alleen de tekst die het moet weergeven.
	 */
	void UpdateTitel();
private slots:
	/**
	 *  Slaat de titel in QDocument, die in de GUI voorstelling wordt gebruikt, op in de interne component.
	 */
	void saveText();
};

#endif // QGRAPHICSTITLEITEM_H_