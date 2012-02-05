//robin timmermans
#if !defined(PAGINA_H)
#define PAGINA_H

#include <list>
#include "Component.h"
#include "foto.h"
#include "tekst.h"
#include "titel.h"
#include "inhoudsopgave.h"
#include "lijst.h"
#include "boekinfo.h"
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
/*  
 *  
 *	de index van m_comp is 0 gebasseerd dus het eerste element heeft index 0
 *  AddComponent(Component * comp) voegt een compent to achteraan de lijst
 *  DelComponent(component * comp) verwijdert het eerste voorkomen van component
 *  DelComponent(int index) verwijdert component met een bepaalde index
 *  NaarVoorgrond(Component * comp) zet de component vooraan in de lijst
 *  NaarAchtergrond(Component *comp) zet de component achteraan in de lijst
 *  AantalComponenten geeft het aantal componenten van de pagina;
 *  
 */
using namespace std;
class Deel;
class Pagina {
public:
	Pagina(Deel* parent = 0);
	Pagina(Pagina & andere);
	~Pagina();
	void AddComponent(Component * comp);
	void DelComponent(Component * comp);
	void DelComponent(int index);
	void NaarVoorgrond(Component * comp);
	void NaarAchtergrond(Component * comp);
	int AantalComponenten()const;
	Component * GetComponent(int index);
	Deel * GetParent()const{return m_parent;}
	void setParent(Deel *parent){m_parent = parent;}
	QDomElement ToXML();
protected:
	list<Component*> m_comp;
	Deel * m_parent;
};

#endif // PAGINA_H