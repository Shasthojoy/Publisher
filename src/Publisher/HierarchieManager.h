// Mathy Vanhoef
// TODO: We kunnen vragen waar dit deel moet komen (index)
// TODO: In Deel Properties kunnen we ook de "index" van dit deel de gebruiken laten veranderen
// MAAR: Eigenlijk is dat al mogenlijk door do "move up" en "move down" buttons. Dus dit is NIET nodig!
#ifndef HIERARCHIEMANAGER_H_
#define HIERARCHIEMANAGER_H_

#include <QtGui/QWidget>

class QTreeWidget;
class QPushButton;
class QTreeWidgetItem;
class LayoutManager;
class Boek;
class Deel;
class Pagina;

/**
 *	Widget die een lijst maakt van alle delen en pagina's. Bied mogenlijkheden om nieuwe delen en pagina's
 *  toe te voegen, wijzigen en verwijderen. Ook de posities van delen/pagina's kunnen worden veranderd.
 */
class HierarchieManager : public QWidget
{
	Q_OBJECT


public:
	HierarchieManager(QWidget *parent = 0);
	/**
	 *	Als het project layouts gebruikt moet de layout manager met deze functie worden ingesteld
	 */
	void SetLayoutManager(LayoutManager *layoutManager) { m_pLayoutManager = layoutManager; }
public slots:
	/**
	 *	Geeft het boek weer in de list.
	 *	@param	boek	Het boek dat moet worden weergegeven
	 */
	void UpdateInfo(Boek *boek);
signals:
	/**
	 *  Signal die wordt verstuurd voordat dit deel wordt verwijderd.
	 */
	void willDeleteDeel(Deel *deel);
	/**
	 *  Signal die wordt verstuurd voordat deze pagina wordt verwijderd.
	 */
	void willDeletePagina(Pagina *pagina);
	/**
	 *  Signal die wordt verstuurd als deze pagina moet worden geopend in de editor
	 */
	void ReqOpenPagina(Pagina *pagina);
	/**
	 *  Signal die wordt verstuurd als er informatie op een pagina kan zijn varanderd.
	 */
	void ReqRefreshPagina();


private:
	/**
	 *  Boek dat wordt weergeven in de Hierarchie Manager
	 */
	Boek *m_pBoek;
	/**
	 *	Layout Manager die het project gebruikt. NULL indien er geen wordt gebruikt.
	 */
	LayoutManager *m_pLayoutManager;
	QTreeWidget *m_pTree;
	QPushButton *m_btnNiewDeel;
	QPushButton *m_btnNiewePagina;
	QPushButton *m_btnVerwijder;
	QPushButton *m_btnWijzig;
	QPushButton *m_btnUp;
	QPushButton *m_btnDown;
	/**
	 *	Enabled het widget
	 */
	void enable();
	/**
	 *	Disabled het widget
	 */
	void disable();
	/**
	 *	Maakt alle widgets van de HierarchieManager aan (list en buttons)
	 */
	QLayout * createWidgets();
	/**
	 *	Geeft de deel en pagina indeces terug van het item
	 *	@param	item		[in]  Widget Item waarvan we de indeces willen weten
	 *	@param	indexDeel	[out] Deel index van het item
	 *	@param	indexPagain	[out] Pagina index van het item. -1 indien het item een deel item it.
	 */
	void getIndeces(QTreeWidgetItem *item, int *indexDeel, int *indexPagina) const;
	/**
	 *	Geeft true terug als een item is geselecteerd. Indien er een item is geselecteerd geven
	 *	de out argument terug welke element is geselecteerd.
	 */
	bool getSelectedIndeces(int *indexDeel, int *indexPagina) const;
	/**
	 *	Update de lijst van delen en pagina's.
	 */
	void UpdateInfo();
private slots:
	void slotItemDoubleClicked(QTreeWidgetItem *item, int column);
	void slotVerwijder();
	void slotWijzig();
	void slotNieuwDeel();
	void slotNiewePagina();
	void slotUp();
	void slotDown();
};

#endif // HIERARCHIEMANAGER_H_