#include "tekst.h"
Tekst::Tekst()
:Component()
{
	
	m_inhoud = "";
}
Tekst::Tekst(const QPoint punt,const QSize & size)
:Component(punt,size)
{
	
	m_inhoud = "";
}
Tekst::Tekst(const QPoint punt,const QSize & size,const QFont &font,const string &inhoud, Pagina *parent /*= 0*/)
:Component(punt,size,font,parent)
{
	m_inhoud = inhoud;
}
Tekst::~Tekst()
{
	//cout<<"destructor tekst";
}
QDomElement Tekst::ToXML()
{
	QString inhoud(m_inhoud.c_str());
    QDomDocument doc;
    QDomElement tekst = doc.createElement( "type" );
	tekst.setAttribute("type",GetType());
	tekst.setAttribute("inhoud", inhoud);
	tekst.appendChild(Component::ToXML());
    return tekst;
}
Component* Tekst::clone()
{
	Component* output = new Tekst(m_punt,m_size,m_font,m_inhoud,m_pParent);
	return output;
}
void Tekst::SetDefault()
{
	m_inhoud = "type hier uw tekst";
}