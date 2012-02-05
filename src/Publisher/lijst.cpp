#include "lijst.h"
Lijst::Lijst()
:Component(), m_lijst()
{
	m_type = LT_PUNTEN;
}
Lijst::Lijst(const QPoint punt,const QSize & size,const QFont font, Pagina *parent /*= 0*/)
:Component(punt,size,parent), m_lijst()
{
	m_type = LT_PUNTEN;
}
Lijst::Lijst(const QPoint punt,const QSize & size,const QFont font, Pagina *parent,const list<string> lijst,const LijstType type)
:Component(punt,size,parent)
{
	m_type = type;
	//m_lijst.operator = (lijst);
	m_lijst = lijst;
}
int Lijst::AantalItems()const
{
	list<string>::size_type lengte;
	lengte = m_lijst.size();
	return lengte;
}
void Lijst::AddItem(string nieuw)
{
	m_lijst.push_back(nieuw);
}
string Lijst::GetItem(int index)const
{
	if(index > AantalItems() - 1 || index < 0)
	{
		ErrorType error = ET_INDEX;
		throw(C_ERROR(error));
	}
	else
	{
		int i = 1;
		list<string>::const_iterator list_IT;
		list_IT = m_lijst.begin();
		while ( i <= index)
		{
			list_IT ++;
			i++;
		}
		return *list_IT;
	}
}
void Lijst::DelItem(int index)
{
	if(index > AantalItems() - 1 || index < 0)
	{
	}
	else
	{
		int i = 1;
		list<string>::iterator list_IT;
		list_IT = m_lijst.begin();
		while ( i <= index)
		{
			list_IT ++;
			i++;
		}
		m_lijst.erase(list_IT);
	}
}
Lijst::~Lijst()
{
	m_lijst.clear();//moet niet worden afgegaan want geen lijst van pointers
	
	//cout<< "\n destructor\n";
}

QDomElement Lijst::ToXML()
{
	QDomDocument doc;
	QDomElement lijst_e = doc.createElement("component");
	lijst_e.setAttribute("type",GetType());
	lijst_e.setAttribute("lijsttype",m_type);
	QDomElement comp = Component::ToXML();
	lijst_e.appendChild(comp);
	QDomElement inhoud = lijstInhoudToXML(m_lijst);
	lijst_e.appendChild(inhoud);

	return lijst_e;

}
QDomElement Lijst::lijstInhoudToXML(std::list<string> lijst)
{
	QDomDocument doc; //is enkel nodig voor qdomelement te kunnen maken
	QDomElement lijst_e = doc.createElement("inhoud");
	list<string>::iterator ITT;
	ITT = lijst.begin();
	while(ITT != lijst.end())
	{
		QString lijstitem((*ITT).c_str());
		QDomElement lijstitem_e = doc.createElement("lijstitem");
		lijstitem_e.setAttribute("inhoud",lijstitem);
		lijst_e.appendChild(lijstitem_e);
		ITT++;
	}
	return lijst_e;

}
void Lijst::clear()
{
	m_lijst.clear();
}
Component* Lijst::clone()
{
	Component* output = new Lijst(m_punt,m_size,m_font,m_pParent,m_lijst,m_type);
	return output;

}
void Lijst::SetDefault()
{
	clear();
	string inhoud = "type hier uw lijst";
	AddItem(inhoud);
	m_type = LT_PUNTEN;
}