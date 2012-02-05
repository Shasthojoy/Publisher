// Mathy Vanhoef
#ifndef EDITOR_H_
#define EDITOR_H_

#include <QtGui/QWidget>

class ComponentList;
class PubGraphicsScene;
class QGraphicsView;
class Pagina;
class Component;

/**
 *	Widget die onderliggend de ComponentList en PubGraphicsScene bestuurd. Het is dus de editor (scene)
 *  en de lijst van component.
 */
class Editor : public QWidget
{
	Q_OBJECT


public:
	Editor(QWidget *parent = 0);
	/**
	 *  Geeft de huidige pagina terug die we aan het editeren zijn.
	 */
	Pagina * GetPaginaEditing() const;
public slots:
	/**
	 *  Maakt de scene leegt en toont de pagina in de scene/editor
	 *	@param	pagina	Pagina die moet worden weergegeven
	 */
	void UpdateInfo(Pagina *pagina);
	/**
	 *	Opent het edit dialoog van de QGraphics component die het interne Component
	 *  comp voorsteld op de scene.
	 *	@param	comp	Interne component waarvoor we het edit dialog moeten oproepen.
	 */
	void WijzigComponent(Component *comp);
signals:
	/**
	 *  Signal die wordt verstuurd als er iets op de pagina is veranderd
	 */
	void InfoHasChanged(Pagina *pagina);


private:
	ComponentList *m_pComp;
	PubGraphicsScene *m_pScene;
	QGraphicsView *m_pView;
	/**
	 *  Pagina die we op het moment aan het editeren zijn. NULL indien geen pagina open is.
	 */
	Pagina *m_pPagina;
private slots:
	/**
	 *  Slot die wordt opgeroepen als er iets in de scene veranderd. Deze stub functie emit het
	 *  InfoHasChanged signal met als argument die huidige pagina die we aan het editeren zijn.
	 */
	void infoHasChangedStub(const QList<QRectF>&);
};

#endif // EDITOR_H_