//robin timmermans
#if !defined(BOEKINFO_H)
#define BOEKINFO_H
 /* 
  *		deze class heeft geen extra membervariabelen omdat
  *     als je een component van het type CT_BoekInfo
  *     tegenkomt je geen extra informatie nodig hebt
  *		verder zijn er nog de get en set functies en de virtuele functies die in component.h zijn uitgelegd.
  */

#include "Component.h"

class BoekInfo : public Component {
public:
	BoekInfo();
	BoekInfo(const QPoint & punt,const QSize & size,const QFont & font,Pagina * parent = 0);
	virtual ComponentType GetType()const{return CT_BOEKINFO;}
	virtual QDomElement ToXML();
	virtual Component* clone();
	virtual void SetDefault(){;}
};

#endif  //BOEKINFO_H
