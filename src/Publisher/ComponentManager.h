// Mathy Vanhoef
#ifndef COMPONENTMANAGER_H_
#define COMPONENTMANAGER_H_

#include <QtGui/QWidget>

class Pagina;
class QTreeWidget;
class QVBoxLayout;
class QPushButton;
class Component;

enum ComponentType;

/**
 *	Widget die de verschillende componenten van een pagina in een lijst toont. Het bied ook de nodige
 *	operaties om deze componenten te kunnen verwijderen en editeren.
 */
class ComponentManager : public QWidget
{
	Q_OBJECT


public:
	ComponentManager(QWidget *parent = 0);
public slots:
	void UpdateInfo(Pagina *pagina);
signals:
	/**
	 *	Signaal dat wordt verstuurd als de gebruiker een component will editeren
	 */
	void ReqWijzigComponent(Component *comp);
	/**
	 *	Signaal dat wordt verstuurd als er een component is verwijderd/gewijzigd.
	 */
	void InfoHasChanged(Pagina *pagina);


private:
	QTreeWidget *m_pTree;
	QPushButton *m_pBtnVerwijder;
	QPushButton *m_pBtnWijzig;
	/**
	 *	Pagina die wordt weergegeven
	 */
	Pagina *m_pPagina;
	/**
	 *	Converteerd de ComponentType naar een QString om te tonen in de lijst
	 */
	QString typeToString(ComponentType type) const;
	/**
	 *	Maak de widget aan die in de component manager worden getoond
	 */
	QVBoxLayout * createWidgets();
	/**
	 *	Geeft de geselecteerde index in de tree terug. -1 als geen item is geselecteerd.
	 */
	int getSelectedIndex() const;
	/**
	 *	Enable het component
	 */
	void enable();
	/**
	 *	Disable het component
	 */
	void disable();
private slots:
	/**
	 *	Slot om te reageren als de gebruiker om Wijzig heeft geklikt
	 */
	void wijzigComponent();
	/**
	 *	Slot om te reageren als de gebruiker om Verwijder heeft geklikt
	 */
	void verwijderComponent();
};

#endif // COMPONENTMANAGER_H_