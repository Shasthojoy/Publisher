#include <assert.h>
#include "QGraphicsInhoudComp.h"
#include "QDialogProperties.h"

#include "inhoudsopgave.h"
#include "boek.h"

QGraphicsInhoudComp::QGraphicsInhoudComp(InhoudsOpgave *inhoudsOpgave, QGraphicsItem *parent /*= 0*/)
	 : QGraphicsSmartTextItem(inhoudsOpgave, parent), m_pInhoudIntern(inhoudsOpgave)
{
	// SetFont, SetPos en setTextWidth worden in de constructor van SmartTextItem al opgeroepen!

	updateText();
}

void QGraphicsInhoudComp::updateText()
{
	// Haal het boek op zodat we alle delen kunnen afgaan
	Pagina *pagina = m_pInhoudIntern->GetParent();
	assert(pagina != NULL);
	Deel *deel = pagina->GetParent();
	assert(deel != NULL);
	Boek *boek = deel->GetParent();
	assert(boek != NULL);

	QString text("");

	// Ga alle delen af
	int aantalDelen = boek->AantalDelen();
	for(int i = 0; i < aantalDelen; ++i)
	{
		Deel *deel = boek->GetDeel(i);
		text += QString("%1)\t").arg(i + 1) + QString::fromStdString(deel->GetTitel());
		if(i < aantalDelen - 1) {
			text += "\n";
		}
	}

	// Geef de genereerde inhoudsopgave weer!
	setPlainText(text);
}

/*virtual*/ bool QGraphicsInhoudComp::openEditDialog()
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