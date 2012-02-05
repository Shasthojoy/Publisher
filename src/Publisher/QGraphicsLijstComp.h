// Mathy Vanhoef
#ifndef QGRAPHICSLIJSTCOMP_H_
#define QGRAPHICSLIJSTCOMP_H_

#include <list>
#include <string>
using std::list;
using std::string;

#include "QGraphicsSmartTextItem.h"
#include "lijst.h"

enum LijstType;

/**
 *  Voorstelling van de Lijst component op een QGraphicsScene.
 */
class QGraphicsLijstComp : public QGraphicsSmartTextItem
{
public:
	QGraphicsLijstComp(Lijst *lijst, QGraphicsTextItem *parent = 0);
	void SetLijstType(LijstType type);
	/*virtual*/ bool openEditDialog();
	/*virtual*/ Component * getComponent() const { return m_pLijstIntern; }


protected:
	/*virtual*/ void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);


private:
	Lijst *m_pLijstIntern;
	/**
	 *  Is de gebruiker momenteel het component aan het resizen?
	 */
	bool m_resizing;
	/**
	 *  Zet de lijst die in de interne component is opgeslagen om naar een QString
	 *	@param	includePrefix	Indien true, zet er ook de Punten, Nummers, etc voor.
	 */
	QString lijstToText(bool includePrefix);
	/**
	 *  Slaat de lijst van strings op in de interne component
	 *	@param	lijst	lijst items die moeten worden opgeslagen
	 */
	void QGraphicsLijstComp::textToLijst(const list<string> &lijst);
	/**
	 *  Genereerd en set de tekst die de op de scene wordt weergegeven.
	 */
	inline void QGraphicsLijstComp::updateText();
	/**
	 *  Veranderd de cursor indien deze rechts onderaan het component is naar de "resize cursor".
	 */
	void handleResizeCursor(const QGraphicsSceneHoverEvent *event);
	/**
	 *  Geeft de string representatie terug van het lijst type prefix
	 *  @param	no		Index van het item in de lijst
	 *  @param	type	Type van de lijst: nummers, punten, ..
	 */
	string prefixLijst(int no, LijstType type);
};

#endif // QGRAPHICSLIJSTCOMP_H_