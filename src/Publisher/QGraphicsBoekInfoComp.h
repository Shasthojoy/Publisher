// Mathy Vanhoef
// TODO: Als ment het edit dialog weergeeft ook de opties geven om de boek informatie zelf te veranderen
#ifndef QGRAPHICSBOEKINFOCOMP_H_
#define QGRAPHICSBOEKINFOCOMP_H_

#include "QGraphicsSmartTextItem.h"

class BoekInfo;

/**
 *  Voorstelling van de BoekInfo component op een QGraphicsScene.
 */
class QGraphicsBoekInfoComp : public QGraphicsSmartTextItem
{
public:
	QGraphicsBoekInfoComp(BoekInfo *boekInfo, QGraphicsItem *parent = 0);
	/*virtual*/ bool openEditDialog();


private:
	BoekInfo *m_pBoekInfoIntern;
	/**
	 *  Genereerd en set de tekst die de op de scene wordt weergegeven.
	 */
	void updateText();
};

#endif // QGRAPHICSBOEKINFOCOMP_H_