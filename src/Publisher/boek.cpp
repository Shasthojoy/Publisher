#include "boek.h"
//Todo Wat moet er met de hoogte van boek?

Boek::Boek()
:m_delen(),m_boekInfo()
{
}

Boek::Boek(const string &titel,const string &versie,const QSize size)
:m_delen(),m_boekInfo(titel,versie,size)
{
}

void Boek::AddDeel(Deel *deel)
{
	m_delen.push_back(deel);
	deel->setParent(this);
}

void Boek::AddDeel(int index, Deel *deel)
{
	list<Deel*>::iterator ITT;
	int i = 0;

	ITT = m_delen.begin();

	while(ITT != m_delen.end() && index != i)
	{
		ITT++;
		i++;
	}
	if(ITT != m_delen.end())
	{
		m_delen.insert(ITT, deel);
	}
}
void Boek::DelDeel(Deel *deel)
{
	list<Deel *>::iterator ITT;

	ITT = m_delen.begin();
	// door lijst lopen tot juiste deel bereikt of tot einde
	while (ITT != m_delen.end() && *ITT != deel)
	{
		ITT++;
	}
	//controleren als we bij de deel zijn aangekomen of niet
	if(ITT != m_delen.end())
	{
		delete *ITT;// het gealloceerd geheugen moet ook worden vrij gegeven want het is een pointer;
		m_delen.erase(ITT);
	}
}
void Boek::DelDeel(int index)
{
	list<Deel*>::iterator ITT;
	int i = 0;

	ITT = m_delen.begin();

	while(ITT != m_delen.end() && index != i)
	{
		ITT++;
		i++;
	}
	if(ITT != m_delen.end() )
	{
	    delete *ITT;
		m_delen.erase(ITT);
	}
}
int Boek::AantalDelen()const
{
	list<Deel *>::size_type lengte;
	lengte = m_delen.size();
	return lengte;
}

Deel* Boek::GetDeel(int index)
{
	list<Deel*>::iterator ITT;
	int i = 0;

	ITT = m_delen.begin();

	while(ITT != m_delen.end() && index != i)
	{
		ITT++;
		i++;
	}
	if(ITT != m_delen.end() )
	{
		return *ITT;
	}
	else
	{
		return NULL;
	}
}
void Boek::moveDeelUp(Deel *deel)
{
	list<Deel *>::iterator ITT;
	list<Deel *>::iterator ITT_insert;
	ITT = m_delen.begin();
	ITT_insert = m_delen.begin();
	ITT++;//het eerste deel overslaan want dit kan toch niet omhoog gaan
	while(ITT != m_delen.end() && *ITT != deel)
	{
		ITT_insert = ITT;
		ITT++;
	}
	if(ITT != m_delen.end() && *ITT == deel)
	{
		if(ITT_insert == m_delen.begin())
			m_delen.push_front(deel);
		else
		{
			/*ITT_insert--;*/
			m_delen.insert(ITT_insert,deel);
		}
		m_delen.erase(ITT);
	}
}
void Boek::moveDeelDown(Deel *deel)
{
	list<Deel *>::iterator ITT;
	list<Deel *>::iterator ITT_insert;

	ITT = m_delen.begin();
	ITT_insert = m_delen.begin();
	while(ITT != m_delen.end() && *ITT != deel)
	{
		ITT++;
		ITT_insert = ITT;
		
	}
	//als de itterator de lijst niet volledig is afgelopen
	if( ITT != m_delen.end() && ITT_insert != m_delen.end()) 
	{
		ITT_insert++;
		//als achteraan moet toevoegen
		if(ITT_insert == m_delen.end())
		{
			m_delen.push_back(deel);
		}
		//als tussen in moet toegevoegd
		else
		{
			ITT_insert++;
			m_delen.insert(ITT_insert,deel);
		}
		m_delen.erase(ITT);
	}
}


QDomElement Boek::ToXML()
{
	list<Deel *>::iterator ITT;
    QDomDocument doc;
    QDomElement boek = doc.createElement( "boek" );
	// tijdelijk om te kijken voor inlezen
	boek.setAttribute("test" ,"test");
	//einde tijdelijk
    QDomElement boekinfo = m_boekInfo.ToXML();
    boek.appendChild(boekinfo);
    ITT = m_delen.begin();
    while(ITT != m_delen.end())
    {
		QDomElement dummy = (*ITT)->ToXML();
		boek.appendChild(dummy);
		ITT++;
    }
    return boek;
}

Boek::~Boek()
{
	list<Deel *>::iterator ITT;

	ITT = m_delen.begin();

	while(ITT != m_delen.end())
	{
		delete *(ITT);
		//cout << "\n comp verwijderd \n";
		ITT++;
	}
	m_delen.clear();
}