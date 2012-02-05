#include "inhoudsopgave.h"
InhoudsOpgave::InhoudsOpgave()
:Component()
{
}


InhoudsOpgave::InhoudsOpgave(const QPoint &punt, const QSize &size,const QFont & font,Pagina *parent)
:Component(punt,size,font,parent)
{
}
QDomElement InhoudsOpgave::ToXML()
{
    QDomDocument doc;
    QDomElement inhoudsopgave = doc.createElement( "type" );
	inhoudsopgave.setAttribute("type",GetType());
	inhoudsopgave.appendChild(Component::ToXML());
    return inhoudsopgave;

}
Component* InhoudsOpgave::clone()
{
	Component * output = new InhoudsOpgave(m_punt,m_size,m_font,m_pParent);
	return output;

}