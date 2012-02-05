#include "titel.h"
Titel::Titel()
:Component()
{
	m_inhoud = "Subtitel";
	m_isDeelTitel = false;
}
Titel::Titel(const QPoint punt,const QSize & size)
:Component(punt,size)
{
	m_inhoud = "Subtitel";
	m_isDeelTitel = false;
}
Titel::Titel(const QPoint punt,const QSize & size,const QFont font, Pagina *parent,const string &inhoud,const bool isdeeltitel)
:Component(punt,size,font,parent)
{
	m_inhoud = inhoud;
	m_isDeelTitel = isdeeltitel;
}
Titel::~Titel()
{
	//cout << "destructor titel";
}
QDomElement Titel::ToXML()
{
	QString inhoud(m_inhoud.c_str());
    QDomDocument doc;
    QDomElement titel = doc.createElement( "component" );
	titel.setAttribute("type",GetType());
	titel.setAttribute("inhoud", inhoud);
	titel.setAttribute("deeltitel", m_isDeelTitel);
	titel.appendChild(Component::ToXML());
    return titel;
}
Component* Titel::clone()
{
	Component * output = new Titel(m_punt,m_size,m_font,m_pParent,m_inhoud,m_isDeelTitel);
	return output;
}
void Titel::SetDefault()
{
	m_inhoud = "Type hier uw titel";
	m_isDeelTitel = false;
}