//robin timmermans
#if !defined(COMPONENT_H)
#define COMPONENT_H

#include <QPoint>
#include <QFont>
#include <Qsize>
#include <QDomNode>
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
// geen include van pagina.h want dit geeft een lus bij de includes 
// en omdat we in de component module geen functies van Pagina aanroepen
class Pagina; //omdat compiler Pagina zal herkennen;
enum ComponentType{
	CT_TEKST,
	CT_FOTO,
	CT_TITEL,
	CT_LIJST,
	CT_INHOUDSOPGAVE,
	CT_BOEKINFO
};
/*
 *  In m_punt staat de possitie waar de component staat op het blad ( een xpos en ypos)
 *  In m_size staan de afmetingen van de component (width en height)
 *  In m_font staat de font van de component
 *  In m_pParent wordt een pointer naar de pagina waar de component op staat.
 *	de destructor heeft geen body  want de pagina moet niet worden verwijderd wanneer component wordt verwijderd
 *  de virtual functie ToXML() geeft een QDomElement representatie van een component. 
 *  deze is vitual gemaakt zodat de juiste functie wordt aangeroepen.
 *  de clone() functie geeft een pointer naar een coppy terug. als je deze functie aanroep wordt je verwacht er zelf voor
 *  te zorgen dat het geheugen wordt vrij gegeven. In dit publisher doet de gui dat omdat de parent goed geset is.
 *  setdefault is hier puur virtueel omdat ge met setdefault enkel inhoud van componenten kan aanpassen niet de layout.
 */
class Component 
{
public:
	Component();
	Component(const QPoint& punt,const QSize & size,Pagina *parent = 0);
	Component(const QPoint& punt,const QSize & size,const QFont & font,Pagina *parent = 0);
	QPoint GetPunt()const {return m_punt;}
	void SetPunt(const QPoint& punt){ m_punt = punt;}
	QSize GetSize()const{return m_size;}
	void SetSize(const QSize size){m_size = size;}
	QFont GetFont()const{return m_font;}
	void SetFont(const QFont & font){m_font = font;}
	Pagina * GetParent()const{return m_pParent;}
	void SetParent(Pagina * parent){m_pParent = parent;}
	virtual QDomElement ToXML();
	virtual ComponentType GetType()const = 0;
	virtual ~Component();
	virtual Component* clone() = 0;
	virtual void SetDefault() = 0;
protected:
	QPoint m_punt;
	QSize m_size;
	QFont m_font;
	Pagina* m_pParent;
};


#endif  //COMPONENT_H

