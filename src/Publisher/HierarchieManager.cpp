// Mathy Vanhoef
// TODO: Voor het veranderen van de volgorde van pagina's etc dit kunnen doen m.b.v. drag en drop
#include <assert.h>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QMessageBox>
#include "HierarchieManager.h"
#include "QDialogDeelProperties.h"
#include "LayoutManager.h"

#include "boek.h"

HierarchieManager::HierarchieManager(QWidget *parent) : QWidget(parent), m_pLayoutManager(NULL)
{
	disable();

	setLayout(createWidgets());

	// Doubleclick to open page
	connect(m_pTree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)), this, SLOT(slotItemDoubleClicked(QTreeWidgetItem*, int)));
	// Connect buttons
	connect(m_btnVerwijder, SIGNAL(clicked()), this, SLOT(slotVerwijder()));
	connect(m_btnWijzig, SIGNAL(clicked()), this, SLOT(slotWijzig()));
	connect(m_btnNiewDeel, SIGNAL(clicked()), this, SLOT(slotNieuwDeel()));
	connect(m_btnUp, SIGNAL(clicked()), this, SLOT(slotUp()));
	connect(m_btnDown, SIGNAL(clicked()), this, SLOT(slotDown()));
	connect(m_btnNiewePagina, SIGNAL(clicked()), this, SLOT(slotNiewePagina()));
}

QLayout * HierarchieManager::createWidgets()
{
	// List
	m_pTree = new QTreeWidget();
	m_pTree->headerItem()->setText(0, "Hierarchie");

	// Nieuwe stuff
	m_btnNiewDeel = new QPushButton("Nieuw Deel");
	m_btnNiewePagina = new QPushButton("Nieuwe Pagina");
	QHBoxLayout *hboxNieuw = new QHBoxLayout();
	hboxNieuw->addWidget(m_btnNiewDeel);
	hboxNieuw->addWidget(m_btnNiewePagina);

	// Edit stuff
	m_btnUp = new QPushButton("<");
	m_btnUp->setMaximumSize(25, 23);
	m_btnDown = new QPushButton(">");
	m_btnDown->setMaximumSize(25, 23);
	m_btnVerwijder = new QPushButton("Verwijder");
	m_btnWijzig = new QPushButton("Wijzig");
	QHBoxLayout *hboxEdit = new QHBoxLayout();
	hboxEdit->addWidget(m_btnUp);
	hboxEdit->addWidget(m_btnDown);
	hboxEdit->addWidget(m_btnWijzig);
	hboxEdit->addWidget(m_btnVerwijder);

	// Main layout
	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->addWidget(m_pTree);
	vbox->addLayout(hboxNieuw);
	vbox->addLayout(hboxEdit);

	return vbox;
}

void HierarchieManager::UpdateInfo(Boek *boek)
{
	m_pBoek = boek;
	m_pTree->clear();

	if(m_pBoek != NULL)
	{
		int aantalDelen = boek->AantalDelen();
		int paginaNo = 1;

		enable();

		if(aantalDelen == 0)
		{
			qWarning("HierarchieManager::UpdateInfo: Trying to load boek with no delen");
			// Maar er is dus wel een boek open: waarschijnlijk heeft de gebruiker het enigste deel
			// verwijder, of heeft hij een lege boek geladen van file, etc
			return;
		}

		// Ga elk deel af
		for(int deelIndex = 0; deelIndex < aantalDelen; ++deelIndex)
		{
			Deel *deel = m_pBoek->GetDeel(deelIndex);
			int aantalPaginas = deel->AantalPaginas();

			QTreeWidgetItem *item = new QTreeWidgetItem(m_pTree, QStringList(QString::fromStdString(deel->GetTitel())));

			if(aantalPaginas == 0)
			{
				// Go to next deel
				continue;
			}

			for(int i = 0; i < aantalPaginas; ++i)
			{
				new QTreeWidgetItem(item, QStringList(QString("Pagina %1").arg(paginaNo)));
				paginaNo++;
			}
		}
	}
	else
	{
		disable();
	}
}

void HierarchieManager::UpdateInfo()
{
	assert(m_pBoek != NULL);
	UpdateInfo(m_pBoek);
}

void HierarchieManager::getIndeces(QTreeWidgetItem *item, int *indexDeel, int *indexPagina) const
{
	QTreeWidgetItem *parent = item->parent();

	// Deel
	if(parent != NULL)
	{
		// Get index of pagina
		*indexPagina = parent->indexOfChild(item);
	}
	else
	{
		*indexPagina = -1;
		parent = item;
	}

	// Get index of deel
	*indexDeel = 0;
	while(parent = m_pTree->itemAbove(parent))
	{
		if(parent->parent() == NULL)
		{
			(*indexDeel)++;
		}
	}
}

bool HierarchieManager::getSelectedIndeces(int *indexDeel, int *indexPagina) const
{
	if(m_pTree->selectedItems().isEmpty())
	{
		return false;
	}

	// Get current selected item
	QTreeWidgetItem *item = m_pTree->currentItem();

	// Now "calculate" the index of this item, zero based.
	getIndeces(item, indexDeel, indexPagina);

	return true;
}

void HierarchieManager::slotItemDoubleClicked(QTreeWidgetItem *item, int)
{
	int indexDeel, indexPagina;

	getIndeces(item, &indexDeel, &indexPagina);

	if(indexPagina != -1)
	{
		Deel *deel = m_pBoek->GetDeel(indexDeel);
		assert(deel != NULL);
		Pagina *pagina = deel->GetPagina(indexPagina);
		assert(pagina != NULL);

		emit ReqOpenPagina(pagina);
	}
}

void HierarchieManager::slotVerwijder()
{
	int indexDeel, indexPagina;

	// Is er iets geselecteerd?
	if(!getSelectedIndeces(&indexDeel, &indexPagina))
	{
		QMessageBox box(QMessageBox::Information, "Selectie fout", "Er is geen component geselecteerd!");
		box.exec();
		return;
	}

	if(indexPagina != -1)
	{
		// Verwijder pagina
		Deel *deel = m_pBoek->GetDeel(indexDeel);
		assert(deel != NULL);
		Pagina *pagina = deel->GetPagina(indexPagina);
		assert(pagina != NULL);

		// Warn other components if they are displaying this page!
		emit willDeletePagina(pagina);

		deel->DelPagina(pagina);
	}
	else
	{
		// Verwijder deel
		Deel *deel = m_pBoek->GetDeel(indexDeel);
		assert(deel != NULL);

		// Warn other components if they are displaying data of this deel!
		emit willDeleteDeel(deel);

		m_pBoek->DelDeel(deel);
	}

	UpdateInfo();
}

void HierarchieManager::slotWijzig()
{
	int indexDeel, indexPagina;

	// Als er niets is geselecteerd
	if(!getSelectedIndeces(&indexDeel, &indexPagina))
	{
		QMessageBox box(QMessageBox::Information, "Selectie fout", "Er is geen component geselecteerd!");
		box.exec();
		return;
	}

	// Als een deel is geselecteerd
	if(indexPagina != -1)
	{
		Deel *deel = m_pBoek->GetDeel(indexDeel);
		assert(deel != NULL);
		Pagina *pagina = deel->GetPagina(indexPagina);
		assert(pagina != NULL);

		emit ReqOpenPagina(pagina);
	}
	// Als een pagina is geselecteerd
	else
	{
		Deel *deel = m_pBoek->GetDeel(indexDeel);

		QDialogDeelProperties dialog;
		dialog.SetTitel(QString::fromStdString(deel->GetTitel()));

		if(dialog.exec())
		{
			deel->SetTitel(dialog.GetTitel().toStdString());
		}

		UpdateInfo();
		// Zodat editor ook wordt geupdate!
		emit ReqRefreshPagina();
	}
}

void HierarchieManager::slotNieuwDeel()
{
	Deel *deel = new Deel("Nieuw Deel");

	QDialogDeelProperties dialog;
	dialog.SetTitel("Nieuw Deel");

	if(dialog.exec())
	{
		deel->SetTitel(dialog.GetTitel().toStdString());
		m_pBoek->AddDeel(deel);
		UpdateInfo();
		emit ReqRefreshPagina();
	}
	else
	{
		delete deel;
		deel = NULL;
	}
}

void HierarchieManager::slotUp()
{
	int indexDeel, indexPagina;

	assert(m_pBoek != NULL);

	// Als er niets is geselecteerd
	if(!getSelectedIndeces(&indexDeel, &indexPagina))
	{
		QMessageBox box(QMessageBox::Information, "Selectie fout", "Er is geen component geselecteerd!");
		box.exec();
		return;
	}

	// Als we een deel hebben geselecteerd
	if(indexPagina == -1)
	{
		m_pBoek->moveDeelUp(m_pBoek->GetDeel(indexDeel));
	}
	// Als we een pagina hebben geselecteerd
	else
	{
		// Als we we gewoon omhoog kunnen "duwen"
		if(indexPagina > 0)
		{
			Deel *deel = m_pBoek->GetDeel(indexDeel);
			deel->movePaginaUp(deel->GetPagina(indexPagina));
		}
		// Anders gaan we hem in het andere deel zetten
		else if(indexDeel > 0)
		{
			Deel *deel = m_pBoek->GetDeel(indexDeel);
			Pagina *pagina = deel->GetPagina(indexPagina);
			deel->ExludePagina(pagina);

			m_pBoek->GetDeel(indexDeel - 1)->AddPagina(pagina);
		}
	}

	UpdateInfo();
}

void HierarchieManager::slotDown()
{
	int indexDeel, indexPagina;

	assert(m_pBoek != NULL);

	// Als er niets is geselecteerd
	if(!getSelectedIndeces(&indexDeel, &indexPagina))
	{
		QMessageBox box(QMessageBox::Information, "Selectie fout", "Er is geen component geselecteerd!");
		box.exec();
		return;
	}

	// Deel geselecteerd
	if(indexPagina == -1)
	{
		// TODO: Eens we een functie krijgen die als argument in index meekrijgt
		m_pBoek->moveDeelDown(m_pBoek->GetDeel(indexDeel));
	}
	// Pagina geselecteerd
	else
	{
		Deel *deel = m_pBoek->GetDeel(indexDeel);

		// Als we we gewoon omlaag kunnen "duwen"
		if(indexPagina < deel->AantalPaginas() - 1)
		{
			deel->movePaginaDown(deel->GetPagina(indexPagina));
		}
		// Anders gaan we hem in het andere deel zetten
		else if(indexDeel < m_pBoek->AantalDelen() - 1)
		{
			Pagina *pagina = deel->GetPagina(indexPagina);
			deel->ExludePagina(pagina);

			m_pBoek->GetDeel(indexDeel + 1)->AddPagina(pagina);
		}
	}

	UpdateInfo();
}

void HierarchieManager::slotNiewePagina()
{
	int indexDeel, indexPagina;

	assert(m_pBoek != NULL);

	// Als er niets is geselecteerd
	bool selected = getSelectedIndeces(&indexDeel, &indexPagina);
	if(!selected || indexPagina != -1)
	{
		QMessageBox box(QMessageBox::Information, "Selectie fout", "Selecteer het deel waarin de pagina moet worden toegevoegd.");
		box.exec();
		return;
	}

	Pagina *nieuw;
	// If we were given a layout, use it!
	if(m_pLayoutManager != NULL)
	{
		nieuw = m_pLayoutManager->GetPaginaLayout();
		// If the user clicked on cancel
		if(nieuw == NULL)
		{
			return;
		}
	}
	else
	{
		nieuw = new Pagina();
	}

	m_pBoek->GetDeel(indexDeel)->AddPagina(nieuw);
	UpdateInfo();
}

inline void HierarchieManager::enable()
{
	this->setEnabled(true);
}

inline void HierarchieManager::disable()
{
	this->setEnabled(false);
}