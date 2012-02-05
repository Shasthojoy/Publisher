#if !defined(BOEK_H)
#define BOEK_H

 /*
  *  AddDeel(Deel* deel) voegt een deel toe achteraan de lijst
  *	 AddDeel(int index, Deel* deel) voegt een deel toe na een bepaalde index
  *  DelDeel(int index) verwijdert het deel op een bepaalde index 
  *  DelDeel(Deel* deel) verwijdert het eerste voorkomen van deel
  *  AantalDelen() geeft het aantal delen van het boek terug
  *	 GetDeel(int index) geeft het deel met een bepaalde index terug
  *	 moveDeelUp(Deel * deel) zet een bepaald deel een positie hoger in de lijst
  *	 moveDeelDown(Deel *deel) zet een bepaald deel een positie lager in de lijst
  */
#include <vector>
#include "boekinformatie.h"
#include "deel.h"
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>

class Boek {
public:
	Boek();
	Boek(const string & titel,const string & versie,const QSize size);
	void AddDeel(Deel* deel);
	void AddDeel(int index, Deel* deel);
	void DelDeel(int index);
	void DelDeel(Deel* deel);
	int AantalDelen()const;
	Deel * GetDeel(int index);
	void moveDeelUp(Deel * deel);
	void moveDeelDown(Deel *deel);
	BoekInformatie & GetBoekInfo(){return m_boekInfo;}
	void SetBoekInfo(BoekInformatie & info){ m_boekInfo = info;}
	QDomElement ToXML();
	~Boek();
private:
	list <Deel*> m_delen;	
	BoekInformatie m_boekInfo;
};

#endif  //BOEK_H