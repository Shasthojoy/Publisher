//robin timmermans
#if !defined(LIJST_H)
#define LIJST_H
/*  nota:
 *  
 *	1)	de index van m_lijst is 0 gebasseerd dus het eerste element heeft index 0
 *
 *	2)	De functies getitem en delitem kunnen een exceptie gooien van het type C_ERROR
 *		dus als ze worden aangeroepen moet gecontroleerd worden als er een exceptie 
 *		wordt gegooid
 */
#include "Component.h"
#include < list >
#include "C_ERROR.h"
 /*
  *   in m_type staat wat voor lijsttype het object is
  *   in m_lijst staat te inhoud van de lijst
  *   de functie clear() is gemaakt om de inhoud te verwijderen.
  *   verder zijn er nog de get en set functies en de virtuele functies die in component.h zijn uitgelegd.
  */

using namespace std;

enum LijstType{
	LT_PUNTEN,
	LT_NUMMERS
};

class Lijst : public Component {
private:
	//hulpfuncties
	QDomElement lijstInhoudToXML(list<string> lijst);
public:
	Lijst();
	Lijst(const QPoint punt,const QSize & size,const QFont font, Pagina * parent = 0);
	Lijst(const QPoint punt,const QSize & size,const QFont font, Pagina * parent ,const list<string> lijst,const LijstType type);
	LijstType GetLijstType()const{return m_type;}
	void SetLijstType(LijstType type){m_type = type;}
	void SetLijstType(int type){m_type = (LijstType)type;}
	int AantalItems()const;
	void AddItem(string nieuw);
	string GetItem(int index)const; 
	void DelItem(int index);  
	virtual ComponentType GetType()const {return CT_LIJST;}
	virtual ~Lijst();
	virtual QDomElement ToXML();
	void clear();
	virtual Component* clone();
	virtual void SetDefault();
protected:
	list<string> m_lijst;
	LijstType m_type;
};

#endif  //LIJST_H