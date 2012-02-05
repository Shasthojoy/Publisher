//robin timmermans
#include "xmlFile.h"

// constroleren van isbn nummer inlezen
xmlboek::xmlboek()
:m_doc("")
{	
	m_bestandsnaam = "naamloos.xml";
}
xmlboek::xmlboek(const string bestandsnaam)
:m_doc()
{
	m_bestandsnaam = bestandsnaam;
}
xmlboek::xmlboek(string bestandsnaam, QDomDocument doc)
{
	m_bestandsnaam = bestandsnaam;
	m_doc = doc;
}
void xmlboek::setDocument(Boek *boek)
{
	m_doc.clear();
	QDomProcessingInstruction instr = m_doc.createProcessingInstruction("xml","version=\"1.0\" ");
	m_doc.appendChild(instr);
	m_doc.appendChild(boek->ToXML());
}

bool xmlboek::opslaan(Boek * boek)
{
	QString bestandsnaam(m_bestandsnaam.c_str());
	QFile outfile(bestandsnaam);
	if(outfile.open(QIODevice::WriteOnly))
	{
		setDocument(boek);
	
		QTextStream stream( &outfile );
		stream << m_doc.toString();

		outfile.close();
		return true;
	}
	else
	{
		return false;		
	}
}
bool xmlboek::opslaan(Boek *boek, QString bestandsnaam)
{
	string bestnm = bestandsnaam.toStdString();
	xmlboek hulp(bestnm);
	return hulp.opslaan(boek);
}
Boek* xmlboek::openen()
{
	QString bestandsnaam(m_bestandsnaam.c_str());
	QFile infile(bestandsnaam);
	if(infile.open(QIODevice::ReadOnly))
	{
		if(m_doc.setContent(&infile))
		{
			infile.close();
		    return getBoek();
		}
		else
		{
			infile.close();
			cerr << "kan file niet parsen" ;
			return NULL;
		}
	}
	else
	{
		cerr << "kan file niet openen";
		return NULL;
	}
}
Boek* xmlboek::openen(QString bestandsnaam)
{
	string bestnm = bestandsnaam.toStdString();
	xmlboek hulp(bestnm);
	return hulp.openen();
}
Boek * xmlboek::getBoek()
{
	Boek * output = new Boek();

	QDomNode boek = m_doc.firstChild();
	boek = boek.nextSibling();
	
	QDomNode boekinfo_n = boek.firstChild();
	
	setboekinfo(boekinfo_n,output);
	
	//delen inlezen gaan vanaf 1 op index 0 staat boekinfo

	QDomNodeList delen = boek.childNodes();
	int aantalDelen = delen.size();
	int deelCursor = 1;
	while(deelCursor < aantalDelen)
	{
		QDomNode deel_n = delen.item(deelCursor);
		Deel *deel = toDeel(deel_n);
		if(deel == NULL)
		{
			delete deel;
			cerr << "parse error";
			return NULL;
		}
		output->AddDeel(deel);
		deelCursor++;
	}
	return output;
}

void xmlboek::setboekinfo(QDomNode boekinfo,Boek *doel)
{
	QDomElement boekinfo_e = boekinfo.toElement();
	
	QDomAttr adresuitgeverij = boekinfo_e.attributeNode("adresuitgeverij");
	string adr = adresuitgeverij.value().toStdString();
	doel->GetBoekInfo().SetAdresUitgeverij(adr);

	QDomAttr titel_a = boekinfo_e.attributeNode("titel");
	string tit = titel_a.value().toStdString();
	doel->GetBoekInfo().SetTitel(tit);

	QDomAttr versie_a = boekinfo_e.attributeNode("versie");
	string versie = versie_a.value().toStdString();
	doel->GetBoekInfo().SetVersie(versie);

	QDomAttr naam_a = boekinfo_e.attributeNode("naamuitgeverij");
	string naam = naam_a.value().toStdString();
	doel->GetBoekInfo().SetNaamUitgeverij(naam);

	QDomAttr editie_a = boekinfo_e.attributeNode("editie");
	string editie = editie_a.value().toStdString();
	doel->GetBoekInfo().SetEditie(editie);

	QDomAttr isbn_a = boekinfo_e.attributeNode("isbn");
	string isbn = isbn_a.value().toStdString();
	doel->GetBoekInfo().SetIsbn(isbn);

	QDomAttr jaardruk_a = boekinfo_e.attributeNode("jaardruk");
	int jaardruk = jaardruk_a.value().toInt();
	doel->GetBoekInfo().SetJaarDruk(jaardruk);

	QSize size;
	QDomAttr width_a = boekinfo_e.attributeNode("width");
	int width = width_a.value().toInt();
	size.setWidth(width);
	QDomAttr height_a = boekinfo_e.attributeNode("height");
	int height = height_a.value().toInt();
	size.setHeight(height);
	doel->GetBoekInfo().SetSize(size);

	QDomNodeList auteurs = boekinfo.firstChild().childNodes();
	
	setauteurs(auteurs,doel);

}
void xmlboek::setauteurs(QDomNodeList auteurs_l, Boek *doel)
{
	int i = 0;
	
	while(i < auteurs_l.size())
	{
		QDomElement auteur_e = auteurs_l.item(i).toElement(); 
		QDomAttr auteur = auteur_e.attributeNode("naam");
		string naam = auteur.value().toStdString();
		doel->GetBoekInfo().AddAuteur(naam);
		i++;
	}
}

QSize xmlboek::toSize(QDomNode size_n)
{
	QDomElement size_e = size_n.toElement();

	QDomAttr height_a = size_e.attributeNode("hoogte");
	QDomAttr width_a = size_e.attributeNode("breedte");
	
	int height = height_a.value().toInt();
	int width = width_a.value().toInt();

	QSize output(width,height);

	return output;
}
QPoint xmlboek::toPoint(QDomNode point_n)
{
	QDomElement point_e = point_n.toElement();

	QDomAttr x_a = point_e.attributeNode("xpos");
	QDomAttr y_a = point_e.attributeNode("ypos");
	
	int x = x_a.value().toInt();
	int y = y_a.value().toInt();

	QPoint output(x,y);

	return output;
}
QFont xmlboek::toFont(QDomNode font_n)
{
	QDomElement font_e = font_n.toElement();
	
	QDomAttr fontfamily_a = font_e.attributeNode("fontfamily");
	QDomAttr pointsize_a = font_e.attributeNode("pointsize");
	QDomAttr fontweight_a = font_e.attributeNode("fontweight");
	QDomAttr italic_a = font_e.attributeNode("italic");
	
	QString fontfamily = fontfamily_a.value();
	int pointsize = pointsize_a.value().toInt();
	int fontweight = fontweight_a.value().toInt();
	int italic = italic_a.value().toInt();
	
	QFont output(fontfamily,pointsize,fontweight,italic);

	return output;
}
Component* xmlboek::toComp(QDomNode component_n)
{
	Component *comp;
	
	QDomElement component_e = component_n.toElement();
	QDomAttr typ_a = component_e.attributeNode("type");
	int type = typ_a.value().toInt();
	switch (type)
	{
	case 0:
		comp = toTekst(component_n);
		break;
	case 1:
		comp = toFoto(component_n);
		break;
	case 2:
		comp = toTitel(component_n);
		break;
	case 3:
		comp = toLijst(component_n);
		break;
	case 4:
		comp = toInhoudsopgave(component_n);
		break;
	case 5:
		comp = toBoekInfo(component_n);
		break;
	default:
		return NULL;
		break;
	}
	return comp;
}
Pagina* xmlboek::toPagina(QDomNode pagina_n)
{
	Pagina * pagina = new Pagina();
	QDomNodeList componenten_l = pagina_n.childNodes();
	int aantalcomponenten = componenten_l.size();
	int componentCursor = 0;
	while(componentCursor < aantalcomponenten)
	{
		QDomNode component_n = componenten_l.item(componentCursor);
		Component *component = toComp(component_n);
		if(component == NULL)
		{
			delete component;
			cerr << "parse error";
			return NULL;
		}
		pagina->AddComponent(component);
		componentCursor++;
	}
	return pagina;

}
Deel* xmlboek::toDeel(QDomNode deel_n)
{
		
	QDomElement deel_e = deel_n.toElement();
	QDomAttr titeldeel_a = deel_e.attributeNode("titel");
	string titeldeel = titeldeel_a.value().toStdString();
	Deel * deel =new Deel(titeldeel);
	//pagina's inlezen
	QDomNodeList paginas = deel_n.childNodes();
	int aantalPaginas = paginas.size();
	int paginaCursor = 0;
	while(paginaCursor < aantalPaginas)
	{
		QDomNode pagina_n = paginas.item(paginaCursor);
		Pagina *pagina = toPagina(pagina_n);
		if(pagina == NULL)
		{
			delete pagina;
			cerr << "parse error";
			return NULL;
		}
		deel->AddPagina(pagina);
		paginaCursor++;
	}
	return deel;
}
Component* xmlboek::toTekst(QDomNode component_n)
{
	Component * comp;
	QDomElement component_e = component_n.toElement();
	QDomAttr inhoud_a = component_e.attributeNode("inhoud");
	string inhoud = inhoud_a.value().toStdString();
	QDomNode layout_n = component_n.firstChild();
	QDomNodeList layout_l = layout_n.childNodes();
	QDomNode point_n = layout_l.item(0);
	QDomNode size_n = layout_l.item(1);
	QDomNode font_n = layout_l.item(2);
	
	QPoint point = toPoint(point_n);
	QSize size = toSize(size_n);
	QFont font = toFont(font_n);
	
    comp = new Tekst(point,size,font,inhoud);

	return comp;
	
}
Component* xmlboek::toFoto(QDomNode component_n)
{
	Component * comp;
	QDomElement component_e = component_n.toElement();
	QDomAttr link_a = component_e.attributeNode("link");
	string link = link_a.value().toStdString();
	QDomAttr beschr_a = component_e.attributeNode("beschrijving");
	string beschr = beschr_a.value().toStdString();

	QDomNode layout_n = component_n.firstChild();
	QDomNodeList layout_l = layout_n.childNodes();
	QDomNode point_n = layout_l.item(0);
	QDomNode size_n = layout_l.item(1);
	QDomNode font_n = layout_l.item(2);
	
	QPoint point = toPoint(point_n);
	QSize size = toSize(size_n);
	QFont font = toFont(font_n);
	
	
	comp = new Foto(point,size,font,link,beschr);

	return comp;
}
Component* xmlboek::toTitel(QDomNode component_n)
{
	Component * comp;
	QDomElement component_e = component_n.toElement();
	QDomAttr inhoud_a = component_e.attributeNode("inhoud");
	string inhoud = inhoud_a.value().toStdString();
	QDomAttr deeltitel_a = component_e.attributeNode("deeltitel");
	int deeltitel = deeltitel_a.value().toInt();

	QDomNode layout_n = component_n.firstChild();
	QDomNodeList layout_l = layout_n.childNodes();
	QDomNode point_n = layout_l.item(0);
	QDomNode size_n = layout_l.item(1);
	QDomNode font_n = layout_l.item(2);
	
	QPoint point = toPoint(point_n);
	QSize size = toSize(size_n);
	QFont font = toFont(font_n);
	
	comp = new Titel(point,size,font,NULL,inhoud,deeltitel);
	return comp;
}
Component* xmlboek::toLijst(QDomNode component_n)
{
	int lijstitemCursor = 0;
	Lijst * comp;
	QDomElement component_e = component_n.toElement();
	QDomAttr lijsttype_a = component_e.attributeNode("lijsttype");
	int lijsttype = lijsttype_a.value().toInt();
	
	QDomNode layout_n = component_n.firstChild();
	QDomNodeList layout_l = layout_n.childNodes();
	QDomNode point_n = layout_l.item(0);
	QDomNode size_n = layout_l.item(1);
	QDomNode font_n = layout_l.item(2);

	QPoint point = toPoint(point_n);
	QSize size = toSize(size_n);
	QFont font = toFont(font_n);

	comp = new Lijst(point,size,font);
	comp->SetLijstType(lijsttype);
	
	QDomNode inhoud_n = layout_n.nextSibling();
	QDomNodeList lijstitems_l = inhoud_n.childNodes();
	while(lijstitemCursor < lijstitems_l.size())
	{
		QDomNode lijstitem_n = lijstitems_l.item(lijstitemCursor);
		QDomElement lijstitem_e = lijstitem_n.toElement();
		QDomAttr lijstitem_a = lijstitem_e.attributeNode("inhoud");
		string lijstitem = lijstitem_a.value().toStdString();
		comp->AddItem(lijstitem);
		lijstitemCursor++;
	}
	return comp;
}
Component* xmlboek::toInhoudsopgave(QDomNode component_n)
{
	Component * comp;
	QDomNode layout_n = component_n.firstChild();
	QDomNodeList layout_l = layout_n.childNodes();
	QDomNode point_n = layout_l.item(0);
	QDomNode size_n = layout_l.item(1);
	QDomNode font_n = layout_l.item(2);

	QPoint point = toPoint(point_n);
	QSize size = toSize(size_n);
	QFont font = toFont(font_n);

	comp = new InhoudsOpgave(point,size,font);
	return comp;
}
Component* xmlboek::toBoekInfo(QDomNode component_n)
{
	Component * comp;
	QDomNode layout_n = component_n.firstChild();
	QDomNodeList layout_l = layout_n.childNodes();
	QDomNode point_n = layout_l.item(0);
	QDomNode size_n = layout_l.item(1);
	QDomNode font_n = layout_l.item(2);

	QPoint point = toPoint(point_n);
	QSize size = toSize(size_n);
	QFont font = toFont(font_n);

	comp = new BoekInfo(point,size,font);
	return comp;
}
