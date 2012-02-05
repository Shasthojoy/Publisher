#include "boekinfo.h"
BoekInfo::BoekInfo()
:Component()
{

}
BoekInfo::BoekInfo(const QPoint &punt, const QSize &size, const QFont &font,Pagina * parent)
:Component(punt,size,font,parent)
{

}
QDomElement BoekInfo::ToXML()
{
	QDomDocument doc;
    QDomElement boekinfo = doc.createElement( "component" );
	boekinfo.setAttribute("type",GetType());
	boekinfo.appendChild(Component::ToXML());
    return boekinfo;
}
Component* BoekInfo::clone()
{
	Component * output = new BoekInfo(m_punt,m_size,m_font,m_pParent);
	return output;
}
