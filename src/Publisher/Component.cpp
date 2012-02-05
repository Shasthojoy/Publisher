#include "Component.h"
#include <iostream>
using namespace std;

Component::Component()
:m_punt(), m_size(),m_font()
{
	m_pParent = NULL;
}
Component::Component(const QPoint& punt,const QSize & size,Pagina *parent/* = 0*/)
: m_font()
{
	m_punt = punt; //standaard assignment operator is genoeg want 2 ints
	m_size = size; //standaard assignment operator is genoeg want 2 ints
	m_pParent = parent;
}

Component::Component(const QPoint& punt,const QSize & size,const QFont & font,Pagina *parent /*= 0*/) 
{
	m_punt = punt;
	m_size = size;
	m_font = font; // operator = is gedefinieerd
	m_pParent = parent;

}
Component::~Component()
{
	//cout<< "\n destructor component\n";
}


QDomElement Component::ToXML()
{
	QDomDocument doc;
    QDomElement cn = doc.createElement( "layout" );
    QDomElement point = doc.createElement("point");
	QDomElement size = doc.createElement("size");
	QDomElement font = doc.createElement("font");
    
	point.setAttribute( "xpos", m_punt.rx() );
    point.setAttribute( "ypos", m_punt.ry() );

    size.setAttribute( "hoogte",m_size.rheight() );
    size.setAttribute( "breedte",m_size.rwidth() );
    
	font.setAttribute( "fontfamily",m_font.family() );
    font.setAttribute( "pointsize",m_font.pointSize() );
    font.setAttribute( "fontweight",m_font.weight() );
    font.setAttribute( "italic",m_font.italic() );
    
    cn.appendChild(point);
	cn.appendChild(size);
	cn.appendChild(font);
    return cn;
}
