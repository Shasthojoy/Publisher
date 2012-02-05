#include <QtGui/QMessageBox>

#include "QDialogKiesLayout.h"
#include "QDialogBeheerLayouts.h"
#include "QDialogLayoutProperties.h"
#include "LayoutManager.h"
#include "xmlfile.h"

LayoutManager::LayoutManager()
{
	m_pLayouts = xmlboek::openen("layouts.pub");
	// If it failed to load layouts, create a new default layout
	if(m_pLayouts == NULL || m_pLayouts->AantalDelen() <= 0)
	{
		qWarning("LayoutManager::LayoutManager: Failed to load layouts");
		
		delete m_pLayouts;
		m_pLayouts = new Boek();
		Deel *layoutEen = new Deel("Lege Pagina");
		layoutEen->AddPagina(new Pagina());
		m_pLayouts->AddDeel(layoutEen);
	}
}

LayoutManager::~LayoutManager()
{
	xmlboek::opslaan(m_pLayouts, "layouts.pub");

	delete m_pLayouts;
}

Pagina * LayoutManager::GetPaginaLayout() const
{
	if(m_pLayouts == NULL || m_pLayouts->AantalDelen() <= 0)
	{
		QMessageBox box(QMessageBox::Information, "Geen Layouts", "Er zijn geen layouts om tussen te kiezen ..");
		box.exec();
		return new Pagina();
	}

	QDialogKiesLayout dialog(m_pLayouts);

	if(dialog.exec())
	{
		Pagina *layout = dialog.getSelectedLayout();
		// Maak een kopie van de layout/pagina als de gebruiker een layout heeft geselecteerd!
		return layout == NULL ? NULL : new Pagina(*layout);
	}

	return NULL;
}

void LayoutManager::MaakLayout(Pagina *pagina)
{
	Pagina *layout = new Pagina(*pagina);

	// Voor elke component moeten we nu de eigenlijke inhoud "verwijderen"
	int aantalComp = layout->AantalComponenten();
	for(int i = 0; i < aantalComp; ++i)
	{
		layout->GetComponent(i)->SetDefault();
	}

	QDialogLayoutProperties dialog;
	dialog.SetNaam("Layout Naam");

	if(dialog.exec())
	{
		// Ok geklikt: sla layout op
		Deel *layoutDeel = new Deel(dialog.GetNaam().toStdString());
		layoutDeel->AddPagina(layout);
		m_pLayouts->AddDeel(layoutDeel);
	}
	else
	{
		// Cancel geklikt: verwijder gealloceerd geheugen
		delete layout;
		layout = NULL;
	}
}

void LayoutManager::BeheerLayouts()
{
	QDialogBeheerLayouts dialog(m_pLayouts);
	dialog.exec();
}