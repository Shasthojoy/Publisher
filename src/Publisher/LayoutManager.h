#ifndef LAYOUTMANAGER_H_
#define LAYOUTMANAGER_H_

#include <QString>
#include <QWidget>

class Pagina;
class Boek;

/**
 *	Klasse om layouts te laden, op te vragen, nieuwe layout te maken en layouts op te slaan.
 *
 *	Layouts worden gezien als een normale pagina. Alle componenten krijgen een
 *	standaard inhoud, grootte, locatie etc. De gebruiker kan de het font en de inhoud
 *	wijzigen terwijl het locatie al perfect is!
 *
 *	Intern worden deze layouts dan ook opgeslagen als een gewoon boek. Elk "deel"
 *	slaat precies een pagina op. De naam van dit deel is dan de naam van de layout
 *	die deze pagina voorsteld.
 *
 */
class LayoutManager : public QWidget
{
	Q_OBJECT

public:
	LayoutManager();
	~LayoutManager();
	/**
	 *  Geeft een pagina terug die de gekozen layout voorsteld. NULL indien cancel!
	 */
	Pagina * GetPaginaLayout() const;
	/**
	 *  Maakt een layout van de huidige pagina met de naam
	 */
	void MaakLayout(Pagina *pagina);
public slots:
	/**
	 *  Geeft lijs van huidige layouts
	 */
	void BeheerLayouts();


private:
	/**
	 *	Hierin worden de layouts opgeslagen
	 */
	Boek *m_pLayouts;
};

#endif // LAYOUTMANAGER_H_