#include "foto.h"
#include <iostream>
using namespace std;
Foto::Foto()
:Component()
{
	m_link = "";
	m_beschr = "beschrijving foto";
}
Foto::Foto(const QPoint &punt,const QSize & size)
:Component(punt,size)
{
	m_link = "";
	m_beschr = "beschrijving foto";
}

Foto::Foto(const QPoint &punt,const QSize & size,const QFont &font,const string &link,const string &beschr,Pagina *parent /* = 0 */)
:Component(punt,size,font,parent)
{
	m_link = link;
	m_beschr = beschr;
}
Foto::~Foto()
{
	//cout << "\n destructor foto\n";
}
QDomElement Foto::ToXML()
{
	QString link(m_link.c_str());
	QString beschr(m_beschr.c_str());
    QDomDocument doc;
    QDomElement foto = doc.createElement( "component" );
	foto.setAttribute("type",GetType());
	foto.setAttribute("link", link);
	foto.setAttribute("beschrijving",beschr);
	QDomElement comp = Component::ToXML();
	foto.appendChild(comp);
    return foto ;

}

Component* Foto::clone()
{
	Component * output = new Foto(m_punt,m_size,m_font,m_link,m_beschr,m_pParent);
	return output;
}
void Foto::SetDefault()
{
	m_link = ":/images/Resources/foto.png";
	m_beschr = "type hier de beschrijving van de foto in";

}