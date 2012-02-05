////voor memory leaks
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>
#include <iostream>
using namespace std;

#include "Pagina.h"


Pagina::Pagina(Deel *parent /*= 0*/)
:m_comp()
{
	m_parent = parent;
}
Pagina::Pagina(Pagina &andere)
{
	list<Component*>::iterator ITT;

	ITT = andere.m_comp.begin();
	while(ITT != andere.m_comp.end())
	{
		// coppy constructor van component aanroepen
		Component * component = (*ITT)->clone();
		// parent van component wijst nog NULL andere moet nu naar this 
		component->SetParent(this);
		m_comp.push_back(component);
		ITT++;
	}
	m_parent = NULL;
}

void Pagina::AddComponent(Component *comp)
{
	m_comp.push_back(comp);
	comp->SetParent(this);
}
void Pagina::DelComponent(Component *comp)
{
	list<Component *>::iterator ITT;

	ITT = m_comp.begin();
	// door lijst lopen tot juiste comp bereikt of tot einde
	while (ITT != m_comp.end() && *ITT != comp)
	{
		ITT++;
	}
	//controleren als we bij de comp zijn aangekomen of niet
	if(ITT != m_comp.end())
	{
		delete *ITT;// het gealloceerd geheugen moet ook worden vrij gegeven want het is een pointer;
		m_comp.erase(ITT);
	}
}
void Pagina::DelComponent(int index)
{
	if(index > AantalComponenten() - 1 || index < 0)
	{
		ErrorType error = ET_INDEX;
		throw(C_ERROR(error));
	}
	else
	{
		list<Component *>::iterator ITT;
		int i = 0;
		
		ITT = m_comp.begin();
		
		while (ITT != m_comp.end() && i < index)
		{
			ITT++;
			i++;
		}
		//controleren als we bij de comp zijn aangekomen of niet
		if(ITT != m_comp.end())
		{
			delete *ITT;// het gealloceerd geheugen moet ook worden vrij gegeven want het is een pointer;
			m_comp.erase(ITT);
		}
	}
}
int Pagina::AantalComponenten()const
{
	list<Component *>::size_type lengte;
	lengte = m_comp.size();
	return lengte;
}
void Pagina::NaarVoorgrond(Component *comp)
{
	list<Component *>::iterator ITT_cursor;

	ITT_cursor  = m_comp.begin();

	// door lijst lopen tot juiste comp bereikt of tot einde
	while (ITT_cursor != m_comp.end() && *ITT_cursor != comp)
	{
		ITT_cursor++;
	}
	//controleren als we bij de comp zijn aangekomen of niet
	if(ITT_cursor != m_comp.end())
	{
		m_comp.push_front(*ITT_cursor);
		m_comp.erase(ITT_cursor);
	}
}
void Pagina::NaarAchtergrond(Component *comp)
{
	list<Component *>::iterator ITT_cursor;

	ITT_cursor  = m_comp.begin();

	// door lijst lopen tot juiste comp bereikt of tot einde
	while (ITT_cursor != m_comp.end() && *ITT_cursor != comp)
	{
		ITT_cursor++;
	}
	//controleren als we bij de comp zijn aangekomen of niet
	if(ITT_cursor != m_comp.end())
	{
		m_comp.push_back(*ITT_cursor);
		m_comp.erase(ITT_cursor);
	}
}
Component* Pagina::GetComponent(int index)
{
	if(index > AantalComponenten() - 1 || index < 0)
	{
		ErrorType error = ET_INDEX;
		throw(C_ERROR(error));
	}
	else
	{
		list<Component *>::iterator ITT;
		int i = 0;
		
		ITT = m_comp.begin();
		
		while (ITT != m_comp.end() && i < index)
		{
			ITT++;
			i++;
		}
		//controleren als we bij de comp zijn aangekomen of niet
		if(ITT != m_comp.end())
		{
			return *ITT;
		}
		else
		{
			return NULL;
		}
	}
}
Pagina::~Pagina()
{
	list<Component *>::iterator ITT;

	ITT = m_comp.begin();

	while(ITT != m_comp.end())
	{
		Component *toDell = *(ITT);
		delete toDell;
		// Mathy:
		*(ITT) = NULL;
		//cout << "\n comp verwijderd \n";
		ITT++;
	}
	m_comp.clear();
}
QDomElement Pagina::ToXML()
{
	list<Component *>::iterator ITT;
    QDomDocument doc;
    QDomElement pagina = doc.createElement( "pagina" );
	ITT = m_comp.begin();
    while(ITT != m_comp.end())
    {
		QDomElement dummy = (*ITT)->ToXML();
		pagina.appendChild(dummy);
		ITT++;
    }
    return pagina;
}
