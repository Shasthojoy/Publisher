//robin timmermans
#if !defined(TITEL_H)
#define TITEL_H

 /*
  *		m_inhoud bevat gewoon de inhoud van de titel
  *     m_isDeelTitel is een boolean om te kijken als de titel een deel titel is 
  *		verder zijn er nog de get en set functies en de virtuele functies die in component.h zijn uitgelegd.
  */
#include "Component.h"
#include < string >


using namespace std;

class Titel : public Component {
public:
	Titel();
	Titel(const QPoint punt,const QSize & size);
	Titel(const QPoint punt,const QSize & size,const QFont font,Pagina * parent,const string & inhoud,const bool isdeeltitel);
	string GetInhoud()const{return m_inhoud;}
	void SetInhoud(const string & inhoud){m_inhoud = inhoud;}
	void SetDeelTitel(bool arg){m_isDeelTitel = arg;}
	bool GetDeelTitel()const{return m_isDeelTitel;}
	virtual ComponentType GetType()const{return CT_TITEL;}
	virtual ~Titel();
	virtual QDomElement ToXML();
	virtual Component* clone();
	virtual void SetDefault();
protected:
	string m_inhoud;
	bool m_isDeelTitel;
};

#endif  //_TITEL_H