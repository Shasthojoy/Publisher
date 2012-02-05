// Mathy Vanhoef
// TODO: Bij het afsluiten vragen als de gebruiker het project eerst will opslaan
#ifndef PROJECTMANAGER_H_
#define PROJECTMANAGER_H_

#include <QObject>

class HierarchieManager;
class ComponentManager;
class Editor;
class Boek;
class Deel;
class Pagina;

/**
 *	Project manager beheert 3 widgets om een boek project te controleren:
 *		- HierarchieManager
 *		- ComponentManager
 *		- Editor
 *
 *	Deze widgets mogen staan waar ze willen, ProjectManager behandeld alleen de interne connecties
 *	tussen deze widgets. Het verbindt dus de signals en slots van deze 3 widgets. Het zorgt er bijvoorbeeld
 *	voor dat als de HierarchieManager een pagina wilt laten toen, dit effectief in de Editor en
 *	ComponentManager gebeurd.
 *	Voor de rest bied het ook de mogenlijkheid om een project te laden, opslaan, sluiten, een nieuwe
 *	project aan te maken, etc.
 */
class ProjectManager : public QObject
{
	Q_OBJECT


public:
	/**
	 *  Alle widgets zijn disabled totdat een project wordt geopened.
	 */
	ProjectManager(HierarchieManager *hierarchie, ComponentManager *component, Editor *editor);
	~ProjectManager();
public slots:
	void NewProject();
	void OpenProject();
	void SaveProject();
	void SaveProjectAs();
	void CloseProject();
	bool EditBoekInfo();
	/**
	 *	Als een pagina wordt verwijderd en deze momenteel wordt weergeven in de Editor of de
	 *	component manager, dan zal project manager deze widgets tijdelijk disablen.
	 */
	void warnDeletionPagina(Pagina *pagina);
	/**
	 *	Als een deel wordt verwijderd en de pagina die wordt getoond in de editor en component manger in dit deel
	 *	zit, dan zal project manager deze widgets tijdelijk disablen.
	 */
	void warnDeletionDeel(Deel *deel);


private:
	/**
	 *  Het boek dat we momenteel aan het bewerken zijn. Project Manager is owner van dit object en is
	 *  dus verantwoordenlijk om het geheugen ervan vrij te geven.
	 */
	Boek *m_pBoek;
	/**
	 *  Pagina die wordt weergegeven in component manager en in editor
	 */
	Pagina *m_pPagina;
	HierarchieManager *m_pHierManager;
	ComponentManager *m_pCompManager;
	Editor *m_pEditor;
	/**
	 *	Als we een project open hebben, en dit ofwel al opgeslagen is of van een file is geopend, zal in deze
	 *  variable de locatie van het bestand staan. Hierdoor kunnen we een "opslaan" functie maken die geen
	 *  filenaam nodig heeft: het verschil tussen save en saveAs!
	 */
	QString m_saveLocation;
	/**
	 *	Sla het huidig project op
	 *	@param	location	Waar we het project moeten opslaan
	 */
	void save(QString location);
	/**
	 *	Open een project.
	 *	@param	location	Locatie van de file
	 */
	void open(QString location);
private slots:
	/**
	 *  Maak dat elk component de info weergeeft over de huidige PAGINA hierover wordt geinformeerd
	 */
	void UpdateBoekInfo(Boek *boek);
	/**
	 *  Maak dat elk component de info weergeeft over her BOEK hierover wordt geinformeerd
	 */
	void UpdatePaginaInfo(Pagina *pagina);
	/**
	 *  Laad automatisch de eerste pagina van het eerste deel als dit bestaat en update de hierarchie
	 */
	void UpdateNewBoek();
	/**
	 *	Refresht de pagina in alle widget die op het moment informatie over die pagina tonen.
	 */
	void RefreshPagina();
};

#endif // PROJECTMANAGER_H_