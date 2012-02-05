//robin timmermans
#if !defined(TEKST_H)
#define TESKST_H
  /*
   *	m_inhoud bevat gewoon de inhoud. 
   *	verder zijn er nog de set en get functies en de virtual functies die in component.h staan uitgelegd
   */

#include "Component.h"
#include < string >

using namespace std;

class Tekst: public Component
{
protected:
	string m_inhoud;
public:
	Tekst();
	Tekst(const QPoint punt,const QSize & size);
	Tekst(const QPoint punt,const QSize & size,const QFont &font,const string & inhoud,Pagina * parent = 0 );
	string GetInhoud()const{return m_inhoud;}
	void SetInhoud(const string & inhoud){m_inhoud = inhoud;}
	virtual ComponentType GetType()const{return CT_TEKST;}
	virtual ~Tekst();
	virtual QDomElement ToXML();
	virtual Component* clone();
	virtual void SetDefault();
};

#endif //TEKST_H