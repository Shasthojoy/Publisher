//robin timmermans
#include <QDomDocument>
#include <QDomNode>
#include <QDomElement>
#include <QDomAttr>
#include <QDomNodeList>
#include <QFile>
#include <QIODevice>
#include <iostream>
#include <QTextStream>
#include "boek.h"
#include <QTextStream>
#include <string>
#include <iostream>
#include <fstream>
#include <QDomEntityReference>
 /*
  *	deze class dient om een xml inte laden of weg te schrijven
  *	deze class heeft twee statische functies zodat je kunt inlezen en uitschrijven zonder een instantie van 
  * xmlboek te maken.
  * opslaan geeft true terug als het schrijven geluk is. 
  * de functie opslaan maakt gebruik van de virtuele functie toxml
  * voor het inlezen zijn de hulpfuncties voorzien.
  */

using namespace std;
class xmlboek
{
private:
	string m_bestandsnaam;
	QDomDocument m_doc;
	
	//hulpfuncties
	
	Boek* getBoek();
	Component* toComp(QDomNode component_n);
	Component* toTekst(QDomNode component_n);
	Component* toFoto(QDomNode component_n);
	Component* toTitel(QDomNode component_n);
	Component* toLijst(QDomNode component_n);
	Component* toInhoudsopgave(QDomNode component_n);
	Component* toBoekInfo(QDomNode component_n);
	Deel * toDeel(QDomNode deel_n);
	Pagina * toPagina(QDomNode pagina_n);
	QPoint toPoint(QDomNode point_n);
	QSize toSize(QDomNode size_n);
	QFont toFont(QDomNode font_n);
	void setauteurs(QDomNodeList auteurs_l,Boek *doel);
	void setboekinfo(QDomNode boekinfo,Boek * doel);
	void setDocument(Boek * boek);
	
	//QString createDTD();
	


public:
	xmlboek();
	xmlboek(const string bestandsnaam);
	
	xmlboek(const string bestandsnaam,const QDomDocument doc);
	
	bool opslaan(Boek *boek);
	static bool opslaan(Boek *boek,QString bestandsnaam);
	
	Boek* openen();
	static Boek* openen(QString bestandsnaam);
};

