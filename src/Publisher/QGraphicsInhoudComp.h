// Mathy Vanhoef
// TODO: Zet er ook pagina nummers bij
#ifndef QGRAPHICSINHOUDCOMP_H_
#define QGRAPHICSINHOUDCOMP_H_

#include "QGraphicsSmartTextItem.h"
#include "IGraphicsComp.h"

class InhoudsOpgave;

/**
 *  Voorstelling van de Inhouds Opgave component op een QGraphicsScene.
 */
class QGraphicsInhoudComp : public QGraphicsSmartTextItem
{
public:
	QGraphicsInhoudComp(InhoudsOpgave *inhoudsOpgave, QGraphicsItem *parent = 0);
	/*virtual*/ bool openEditDialog();


private:
	InhoudsOpgave *m_pInhoudIntern;
	/**
	 *  Genereerd en set de tekst die de op de scene wordt weergegeven.
	 */
	void updateText();
};

#endif // QGRAPHICSINHOUDCOMP_H_