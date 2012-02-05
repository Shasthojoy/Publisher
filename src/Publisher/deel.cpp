#include "deel.h"

Deel::Deel()
:m_paginas()
{
	string titel = "";
	m_titel = titel;
	m_pParent = NULL;
}
Deel::Deel(const std::string &titel )
:m_paginas()
{
	m_titel = titel;
	m_pParent = NULL;
}
void Deel::AddPagina(Pagina* pagina)
{
	m_paginas.push_back(pagina);
	pagina->setParent(this);
}
void Deel::AddPagina(int index, Pagina *pagina)
{
	list<Pagina*>::iterator ITT;
	int i = 0;

	ITT = m_paginas.begin();

	while(ITT != m_paginas.end() && index != i)
	{
		ITT++;
		i++;
	}
	if(ITT != m_paginas.end())
	{
		m_paginas.insert(ITT, pagina);
	}
}

void Deel::DelPagina(Pagina *pagina)
{
	list<Pagina *>::iterator ITT;

	ITT = m_paginas.begin();
	// door lijst lopen tot juiste comp bereikt of tot einde
	while (ITT != m_paginas.end() && *ITT != pagina)
	{
		ITT++;
	}
	//controleren als we bij de comp zijn aangekomen of niet
	if(ITT != m_paginas.end())
	{
		delete *ITT;// het gealloceerd geheugen moet ook worden vrij gegeven want het is een pointer;
		m_paginas.erase(ITT);
	}
}

void Deel::ExludePagina(Pagina *pagina)
{
	list<Pagina *>::iterator ITT;

	ITT = m_paginas.begin();
	// door lijst lopen tot juiste comp bereikt of tot einde
	while (ITT != m_paginas.end() && *ITT != pagina)
	{
		ITT++;
	}
	//controleren als we bij de comp zijn aangekomen of niet
	if(ITT != m_paginas.end())
	{
		m_paginas.erase(ITT);
	}
}

void Deel::DelPagina(int index)
{
	list<Pagina *>::iterator ITT;
	int i = 0;
	
	ITT = m_paginas.begin();
	
	while (ITT != m_paginas.end() && i < index)
	{
		ITT++;
		i++;
	}
	//controleren als we bij de comp zijn aangekomen of niet
	if(ITT != m_paginas.end())
	{
		delete *ITT;// het gealloceerd geheugen moet ook worden vrij gegeven want het is een pointer;
		m_paginas.erase(ITT);
	}
}
int Deel::AantalPaginas() const
{
	list<Pagina *>::size_type lengte;
	lengte = m_paginas.size();
	return lengte;
}
void Deel::movePaginaUp(Pagina *pagina)
{
	list<Pagina *>::iterator ITT;
	list<Pagina *>::iterator ITT_insert;
	ITT = m_paginas.begin();
	ITT_insert = m_paginas.begin();
	ITT++;//het eerste pagina overslaan want dit kan toch niet omhoog gaan
	while(ITT != m_paginas.end() && *ITT != pagina)
	{
		ITT_insert = ITT;
		ITT++;
	}
	if(ITT != m_paginas.end() && *ITT == pagina)
	{
		if(ITT_insert == m_paginas.begin())
			m_paginas.push_front(pagina);
		else
		{
			m_paginas.insert(ITT_insert,pagina);
		}
		m_paginas.erase(ITT);
	}
}
void Deel::movePaginaDown(Pagina *pagina)
{
	list<Pagina *>::iterator ITT;
	list<Pagina *>::iterator ITT_insert;

	ITT = m_paginas.begin();
	ITT_insert = m_paginas.begin();
	while(ITT != m_paginas.end() && *ITT != pagina)
	{
		ITT++;
		ITT_insert = ITT;
		
	}
	//als de itterator de lijst niet volledig is afgelopen
	if( ITT != m_paginas.end() && ITT_insert != m_paginas.end()) 
	{
		ITT_insert++;
		//als achteraan moet toevoegen
		if(ITT_insert == m_paginas.end())
		{
			m_paginas.push_back(pagina);
		}
		//als tussen in moet toegevoegd
		else
		{
			ITT_insert++;
			m_paginas.insert(ITT_insert,pagina);
		}
		m_paginas.erase(ITT);
	}

}

Pagina * Deel::GetPagina(int index)
{
	list<Pagina *>::iterator ITT;
	int i = 0;

	ITT = m_paginas.begin();
	while (ITT != m_paginas.end() && i != index)
	{
		ITT++;
		i++;
	}
	if(ITT != m_paginas.end())
	{
		return *ITT;
	}
	else
	{
		return NULL;
	}
}
QDomElement Deel::ToXML()
{
	QString titel(m_titel.c_str());
	list<Pagina *>::iterator ITT;
    QDomDocument doc;
    QDomElement deel = doc.createElement( "deel" );
	deel.setAttribute("titel", titel);
	ITT = m_paginas.begin();
    while(ITT != m_paginas.end())
    {
		QDomElement dummy = (*ITT)->ToXML();
		deel.appendChild(dummy);
		ITT++;
    }
    return deel;
}
Deel::~Deel()
{
	list<Pagina *>::iterator ITT;

	ITT = m_paginas.begin();

	while(ITT != m_paginas.end())
	{
		delete *(ITT);
		//cout << "\n comp verwijderd \n";
		ITT++;
	}
	m_paginas.clear();
}