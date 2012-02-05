//robin timmermans

#if !defined(DEEL_H)
#define DEEL_H

/*  
 *  
 *	de index van m_paginas is 0 gebasseerd dus het eerste element heeft index 0
 *  AddPagina(Pagina* pagina) voegt een pagina to achteraan de lijst
 *  AddPagina(int index, Pagina * pagina) voegt een pagina in na een bepaalde index;
 *  DelPagina(Pagina * pagina) verwijdert het eerste voorkomen van pagina
 *  DelPagina(int index) verwijdert pagina met een bepaalde index
 *  ExludePagina(Pagina *pagina) doet hetzelfde als delpagina behalve geeft ie het geheugen van pagina niet vrij 
 *  movePaginaUp(Pagina *pagina) zet de pagina een plaats hoger in de lijst;
 *	movePaginaDown(Pagina *pagina) zet de pagina een plaats lager in de lijst;
 *  AantalComponenten geeft het aantal componenten van de pagina;
 *  
 */


#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
#include "Pagina.h"
class Boek;
class Deel {
public:
	Deel();
	Deel(const string & titel );
	void AddPagina(Pagina* pagina);
	void AddPagina(int index, Pagina * pagina);
	void DelPagina(Pagina * pagina);
	void DelPagina(int index);
	void ExludePagina(Pagina *pagina);
	string GetTitel()const{return m_titel;}
	void SetTitel(const string & titel){m_titel = titel;}
	int AantalPaginas()const;
	QDomElement ToXML();
	Pagina * GetPagina(int index);
	Boek * GetParent()const {return m_pParent;}
	void setParent(Boek *parent){m_pParent = parent;}
	void movePaginaUp(Pagina *pagina);
	void movePaginaDown(Pagina *pagina);
	~Deel();
protected:
	string m_titel;
	list<Pagina*> m_paginas;
	Boek * m_pParent;
};

#endif  //DEEL_H