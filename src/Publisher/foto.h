//robin timmermans
#if !defined(FOTO_H)
#define FOTO_H

#include "Component.h"
#include < string >
using namespace std;
 /*
  *		In m_link staat de bestandsnaam van de foto 
  *		In m_beschr staat de beschrijving van de foto
  *		verder zijn er nog de get en set functies en de virtuele functies die in component.h zijn uitgelegd.
  */

class Foto : public Component {
public:
	Foto();
	Foto(const QPoint & punt,const QSize & size);
	Foto(const QPoint & punt,const QSize & size,const QFont & font,const string & link,const string & beschr,Pagina *parent = 0);
	string GetFoto()const {return m_link;}
	void SetFoto(const string & link){m_link = link;}
	string GetBeschrijving()const {return m_beschr;}
	void SetBeschrijving(const string & beschr){m_beschr = beschr;}
	virtual ComponentType GetType()const {return CT_FOTO;}
	virtual QDomElement ToXML();
	virtual ~Foto();
	virtual Component* clone();
	virtual void SetDefault();
protected:
	string m_link;
	string m_beschr;
};

#endif  //_FOTO_H