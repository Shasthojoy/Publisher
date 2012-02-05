#include "boekinformatie.h"

BoekInformatie::BoekInformatie()
:m_auteurs(),m_size()
{
	m_titel = "titel";
	m_versie = "versie";
	m_naamUitgeverij = "naam uitgeverij";
	m_adresUitgeverij = "adres uitgeverij";
	m_isbn = "isbn nummer";
	m_jaarDruk = 2000;
	m_editie = "1ste editie";
}
BoekInformatie::BoekInformatie(const string &titel,const string &versie,const QSize size)
:m_auteurs(),m_size(size)
{
	m_titel = titel;
	m_versie = versie;
	m_naamUitgeverij = "naam uitgeverij";
	m_adresUitgeverij = "adres uitgeverij";
	m_isbn = "isbn nummer";
	m_jaarDruk = 2000;
	m_editie = "1ste editie";

}
void BoekInformatie::AddAuteur(const string &auteur)
{
	m_auteurs.push_back(auteur);
}

void BoekInformatie::DelAuteur(const string &auteur)
{
	vector<string>::iterator ITT;

	ITT = m_auteurs.begin();
	while(ITT != m_auteurs.end() && *ITT != auteur)
	{
		ITT++;
	}
	if(ITT != m_auteurs.end())
	{
		m_auteurs.erase(ITT);
	}
}
int BoekInformatie::AantalAuteurs()
{
	vector<string>::size_type lengte;
	lengte = m_auteurs.size();
	return lengte;
}
string BoekInformatie::GetAuteur(int index)
{
	vector<string>::iterator ITT;
	int i = 0;

	ITT = m_auteurs.begin();

	while(ITT != m_auteurs.end() && i != index)
	{
		ITT++;
		i++;
	}
	if(ITT != m_auteurs.end())
	{
		return *ITT;
	}
	else
	{
		return "";
	}
}
QDomElement BoekInformatie::ToXML()
{
	QString titel(m_titel.c_str());
	QString versie(m_versie.c_str());
	QString naamUitgeverij(m_naamUitgeverij.c_str());
	QString adresUitgeverij(m_adresUitgeverij.c_str());
	QString editie(m_editie.c_str());
	QString isbn(m_isbn.c_str());
   
	QDomDocument doc;
    QDomElement boekinformatie = doc.createElement( "boekinformatie" );

	boekinformatie.setAttribute("titel",titel);
	boekinformatie.setAttribute("versie",versie);
	boekinformatie.setAttribute("naamuitgeverij",naamUitgeverij);
	boekinformatie.setAttribute("adresuitgeverij",adresUitgeverij);
	boekinformatie.setAttribute("editie",editie);
	boekinformatie.setAttribute("isbn",isbn);
	boekinformatie.setAttribute("jaar",m_jaarDruk);
	boekinformatie.setAttribute("width",m_size.rwidth());
	boekinformatie.setAttribute("heigth",m_size.rheight());
	boekinformatie.appendChild(auteursToXML());
	
    return boekinformatie;
}

//hulpfuncties

QDomElement BoekInformatie::auteursToXML()
{
	vector<string>::iterator ITT;
	QDomDocument doc;
    QDomElement auteurs = doc.createElement( "auteurs" );

	ITT = m_auteurs.begin();
	while(ITT != m_auteurs.end())
	{
		QString naam((*ITT).c_str());
		QDomElement auteur = doc.createElement("auteur");
		auteur.setAttribute("naam",naam);
		auteurs.appendChild(auteur);
		ITT++;
	}
	return auteurs;
}
void BoekInformatie::SetAuteurs(vector<string> lijst)
{
	vector<string>::iterator ITT;
	
	//geen vector van pointers dus clear goed genoeg
	m_auteurs.clear();
	ITT = lijst.begin();

	while(ITT != lijst.end())
	{
		m_auteurs.push_back(*ITT);
		ITT++;
	}
}