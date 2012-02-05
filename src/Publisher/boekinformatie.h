#if !defined(BOEKINFORMATIE_H)
 /*
  * in deze klasse staan alle eigenschappen van boek met hun get en set functies
  *
  */

#define BOEKINFORMATIE_H
#include <QSize>
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
#include <vector>
#include <string>
using namespace std;
class BoekInformatie {
public:
	BoekInformatie();
	BoekInformatie(const string &titel,const string &versie,const QSize size);
	string GetNaamUitgeverij()const {return m_naamUitgeverij;}
	void SetNaamUitgeverij(const string & naam){m_naamUitgeverij = naam;}
	string GetAdresUitgeverij()const {return m_adresUitgeverij;}
	void SetAdresUitgeverij(const string & adres){m_adresUitgeverij = adres;}
	string GetIsbn()const{return m_isbn;}
	void SetIsbn(const string & isbn){m_isbn = isbn;}
	int GetJaarDruk()const{return m_jaarDruk;}
	void SetJaarDruk(int jaar){m_jaarDruk = jaar;}
	string GetEditie()const {return m_editie;}
	void SetEditie(const string editie) {m_editie = editie;}
	string GetTitel()const {return m_titel;}
	void SetTitel(const string & titel){m_titel = titel;}
	void AddAuteur(const string & auteur);
	void DelAuteur(const string & auteur);
	vector<string> GetAuteurs(){return m_auteurs;}
	void SetAuteurs(vector<string> lijst);
	int AantalAuteurs();
	string GetAuteur(int index);
	string GetVersie()const {return m_versie;}
	void SetVersie(const string & versie){m_versie = versie;}
	void SetSize(const QSize & size){m_size = size;}
	QSize GetSize()const{return m_size;}
	QDomElement ToXML();
private:
	string m_titel;
	// er zijn meestal een klein aantal auteurs dus een vector is goed
	vector<string> m_auteurs;
	string m_versie;
	QSize m_size;
	string m_naamUitgeverij;
	string m_adresUitgeverij;
	string m_isbn;
	int m_jaarDruk;
	string m_editie;
	//hulpfuncties
	QDomElement auteursToXML();
};

#endif  //_BOEKINFORMATIE_H