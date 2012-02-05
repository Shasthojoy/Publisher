// Mathy Vanhoef
#ifndef PUBGRAPHICSSCENE_H_
#define PUBGRAPHICSSCENE_H_

#include <QtGui/QGraphicsScene>

#include "component.h"
#include "lijst.h"

class QGraphicsSceneDragDropEvent;
class Pagina;
class QVariant;

/**
 *	QGraphicsScene die een pagina kan renderen. Ook zorgt het voor het drag en drop van nieuwe componenten
 *  vanuit de ComponentList en voegt deze automatisch aan de pagina en scene. Het reageerd ook op SHIFT+DEL
 *  om geselecteerde component te verwijderen. Bied ook de mogenlijk om, gegeven een pointer naar een intern
 *  component, het dialoog voor de eigenschappen van dit component weer te geven (indien dit component zich in
 *  de huidge pagina die open is bevindt).
 *
 *
 *
 *  We steunen nu op het signal changed(const QList<QRectF>&) van QGraphicsScene
 *  om veranderingen te detecteren. Dit is niet optimaal! Voor de toekomst zou het
 *  beten zijn om hiervoor zelf een signal te maken. Een nadeel van de huidge
 *  implementatie is dat dit signal (te) veel verzonden worden terwijl dit niet altijd nodig is!
 *  Als bijvoorbeeld een element geselecteerd wordt zal het al een signal verzenden
 *	terwijl dit niet nodig is.
 *
 *
 *
 *  Bij het toevoegen van een nieuw component moeten de volgende functies worden geupdate:
 *	 - render(Pagina *pagina)
 *	 - createNewComponent(const QPointF &pos, ComponentType type, QVariant &arg)
 */
class PubGraphicsScene : public QGraphicsScene
{
	Q_OBJECT


public:
	PubGraphicsScene(QObject *parent = 0);
	/**
	 *	Roept het properties dialog op van het component. Als het component niet voorkomt in
	 *	de scene doet deze functie niets.
	 *	@param	comp	Component waarvan men het dialoog wil weergeven.
	 */
	void WijzigComponent(Component *comp);
public slots:
	/**
	 *	Geef de pagina weer in de sceen
	 *	@param	pagina	Pagina die je wil weergeven
	 */
	void UpdateInfo(Pagina *pagina);


protected:
	/*virtual*/ void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
	/*virtual*/ void dragMoveEvent(QGraphicsSceneDragDropEvent *event);
	/**
	 *  Als het een "publisher/new-comp-drag" drop is, maakt dit het component aan in de scene
	 *	en zowel in de interne representatie van de pagina.
	 */
	/*virtual*/ void dropEvent(QGraphicsSceneDragDropEvent *event);
	/**
	 *	Verwijderd de geselecteerde component indien de combinatie SHIFT+DEL is
	 */
	/*virtual*/ void keyPressEvent(QKeyEvent *keyEvent);
	/*virtual*/ void keyReleaseEvent(QKeyEvent *keyEvent);


private:
	bool m_isEnabled;
	bool holdingShift;
	/**
	 *  Pagina die we op het moment aan het editeren zijn.
	 */
	Pagina *m_pPagina;
	/**
	 *  Verwijder alle component op de scene en geeft de pagina weer in de scene
	 */
	void render(Pagina *pagina);
	/**
	 *	Disabled de scene en tekent een grijze achtergrond
	 */
	void disable();
	/**
	 *	Enabled de scene en reset de achtergrond
	 */
	void enable();
	/**
	 *  Maakt een nieuwe component aan met het gegeven type en eventueel een bijkomend argument
	 *  dat afhangt van welk type je een component wil maken. De component wordt gevuld met
	 *  standaard waarden, behavle de locatie wordt ingesteld.
	 *	Het component wordt intern aan de pagina toegevoegd die we op het moment aan het editeren
	 *	zijn, er het wordt ook op de scene onmiddelijk voorgesteld.
	 *
	 *	@param	pos		Waar in de scene het component moet worden gezet
	 *	@param	type	Type van het component dat we moeten aanmaken
	 *	@param	arg		Bijkomend argument dat afhang van het type component.
						Bij een lijst bijvoorbeeld de prefix: punten of nummers
	 */
	void createNewComponent(const QPointF &pos, ComponentType type, QVariant &arg);
	//
	// De volgende functies maken allemaal een grafische en interne voorstelling van het
	// component. Daarna opent het de properties dialog om eigenschappen van het component
	// te veranderen. Het maakt dus een compleet nieuw component aan met default properties
	// en toont dan het dialoog om de eigenschappen ervan de veranderen.
	// @param	pos		[in]  Locatie van het component
	// @param	comp	[out] Pointer naar het component dat wordt aangemaakt
	// @param	item	[out] Pointer naar het Graphics Item dat wordt aangemaakt
	// @param	pagina	[in]  Sommige component moeten een parent hebben om correct te worden
	//							weergeven (zoals inhoudsopgave en boekinfo). Deze moeten (!) we
	//							hier aal meegeven.
	//
	// De functies geven true terug als het component al aan de pagina is toegevoegd.
	// Als comp of item na de functie aanroep nog altijd NULL is, heeft de gebruiker op
	//	cancel geklikt in het dialog en moet de component NIET aan de scene/pagina worden toegevoegd!
	//
	bool addTekstComp(const QPoint pos, Component **comp, QGraphicsItem **item);
	bool addFotoComp(const QPoint pos, Component **comp, QGraphicsItem **item);
	bool addTitelComp(const QPoint pos, Component **comp, QGraphicsItem **item, Pagina *parent);
	bool addLijstComp(const QPoint pos, LijstType type, Component **comp, QGraphicsItem **item);
	bool addIHComp(const QPoint pos, Component **comp, QGraphicsItem **item, Pagina *parent);
	bool addBoekInfoComp(const QPoint pos, Component **comp, QGraphicsItem **item, Pagina *parent);
};

#endif // PUBGRAPHICSSCENE_H_