// Mathy Vanhoef
// TODO: saveText alleen oproepen eens de gebruiker gedaan heeft met typen.
//			Deze functie wordt nu veel uitgevoerd..
#ifndef QGraphicsTekstComp_H_
#define QGraphicsTekstComp_H_

#include "QGraphicsSmartTextItem.h"

class Tekst;
class QCursor;

/**
 *  Voorstelling van de Tekst component op een QGraphicsScene.
 */
class QGraphicsTekstComp : public QGraphicsSmartTextItem
{
	Q_OBJECT


public:
	QGraphicsTekstComp(Tekst *tekst, QGraphicsItem * parent = 0);
	void SetInhoud(const QString &inhoud);
	/*virtual*/ bool openEditDialog();


protected:
	/*virtual*/ void mousePressEvent(QGraphicsSceneMouseEvent *event);


private:
	Tekst *m_pTekstIntern;
private slots:
	/**
	 *  Slaat de tekst van de QDocument, die in de GUI voorstelling wordt gebruikt, op in de interne component.
	 */
	void saveText();
};

#endif // QGraphicsTekstComp_H_