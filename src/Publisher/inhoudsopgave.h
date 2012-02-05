//robin timmermans
#if !defined(INHOUDSOPGAVE_H)
#define INHOUDSOPGAVE_H

 /* 
  *		deze class heeft geen extra membervariabelen omdat
  *     als je een component van het type CT_Inhoudsopgave
  *     tegenkomt je geen extra informatie nodig hebt
  *		verder zijn er nog de get en set functies en de virtuele functies die in component.h zijn uitgelegd.
  */

#include <QPoint>
#include <QFont>
#include <QSize>
#include "Component.h"


class InhoudsOpgave : public Component {
public:
	InhoudsOpgave();
	InhoudsOpgave(const QPoint & punt,const QSize & size,const QFont & font,Pagina *parent = 0);
	virtual ComponentType GetType()const{return CT_INHOUDSOPGAVE;}
	virtual QDomElement ToXML();
	virtual Component* clone();
	virtual void SetDefault(){;}
};

#endif  //INHOUDSOPGAVE_H