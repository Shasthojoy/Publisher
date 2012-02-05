#include <assert.h>
#include <QTextStream>

#include "QGraphicsBoekInfoComp.h"
#include "QDialogProperties.h"
#include "boekinfo.h"
#include "boek.h"

QGraphicsBoekInfoComp::QGraphicsBoekInfoComp(BoekInfo *boekInfo, QGraphicsItem *parent /*= 0*/)
	 : QGraphicsSmartTextItem(boekInfo, parent), m_pBoekInfoIntern(boekInfo)
{
	// SetFont, SetPos en setTextWidth worden in de constructor van SmartTextItem al opgeroepen!

	updateText();
}

void QGraphicsBoekInfoComp::updateText()
{
	// Haal boek informatie op
	Pagina *pagina = m_pBoekInfoIntern->GetParent();
	assert(pagina != NULL);
	Deel *deel = pagina->GetParent();
	assert(deel != NULL);
	Boek *boek = deel->GetParent();
	assert(boek != NULL);
	BoekInformatie &info = boek->GetBoekInfo();

	// Genereer de eigenlijk teksts

	// Titel
	QString deelEen("Titel:\t\t");
	deelEen += QString::fromStdString(info.GetTitel()) + "\n";

	// Ga alle auteurs af
	QString deelTwee("Auteurs:");
	int aantalAuteurs = info.AantalAuteurs();
	if(aantalAuteurs == 0)
	{
		deelTwee += "\n";
	}
	else
	{
		for(int i = 0; i < aantalAuteurs; ++i)
		{
			deelTwee += QString::fromStdString("\t\t" + info.GetAuteur(i) + "\n");
		}
	}

	// Rest van de info
	QString deelDrie;
	QTextStream strDeelDrie(&deelDrie);
	strDeelDrie << "Versie:\t\t" << info.GetVersie().c_str()
		<< "\nGrootte:\t\t" << info.GetSize().width() << " x " << info.GetSize().height()
		<< "\nNaam Uitgeverij:\t" << info.GetNaamUitgeverij().c_str()
		<< "\nAdres Uitgeverij:\t" << info.GetAdresUitgeverij().c_str()
		<< "\nISBN:\t\t" << info.GetIsbn().c_str()
		<< "\nJaar druk:\t\t" << info.GetJaarDruk()
		<< "\nEditie:\t\t" << info.GetEditie().c_str();

	// Geef nu deze tekst weer
	setPlainText(deelEen + deelTwee + deelDrie);
}

/*virtual*/ bool QGraphicsBoekInfoComp::openEditDialog()
{
	QDialogProperties dialog;

	// Set properties of dialog
	dialog.SetPos(pos().toPoint());
	dialog.SetSize(boundingRect().size().toSize());
	dialog.SetFont(font());
	dialog.disableHoogte();

	// Open dialog
	bool rval = dialog.exec();
	if(rval)
	{
		SetPunt(dialog.GetPos());
		SetFont(dialog.GetFont());
		SetSize(dialog.GetSize().width());
	}

	return rval;
}