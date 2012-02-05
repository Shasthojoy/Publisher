// Mathy Vanhoef
#include <assert.h>
#include <QtGui/QTreeWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QMessageBox>
#include <QStringList>

#include "ComponentManager.h"
#include "Pagina.h"

ComponentManager::ComponentManager(QWidget *parent) : QWidget(parent)
{
	// Create this widget
	setLayout(createWidgets());

	// Create actions
	connect(m_pBtnWijzig, SIGNAL(clicked()), this, SLOT(wijzigComponent()));
	connect(m_pBtnVerwijder, SIGNAL(clicked()), this, SLOT(verwijderComponent()));
}

QVBoxLayout * ComponentManager::createWidgets()
{
	// TODO: Resize column width
	m_pTree = new QTreeWidget();
	m_pTree->headerItem()->setText(0, "Component");
	m_pTree->headerItem()->setText(1, "x");
	m_pTree->headerItem()->setText(2, "y");
	m_pTree->setColumnCount(3);

	// Edit stuff
	m_pBtnVerwijder = new QPushButton("Verwijder");
	m_pBtnWijzig = new QPushButton("Wijzig");
	QHBoxLayout *hboxEdit = new QHBoxLayout();
	hboxEdit->addWidget(m_pBtnWijzig);
	hboxEdit->addWidget(m_pBtnVerwijder);

	// Main layout
	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->addWidget(m_pTree);
	vbox->addLayout(hboxEdit);

	return vbox;
}

QString ComponentManager::typeToString(ComponentType type) const
{
	switch(type)
	{
	case CT_TEKST: return "Teksts";
	case CT_FOTO: return "Foto";
	case CT_TITEL: return "Titel";
	case CT_LIJST: return "Lijst";
	case CT_INHOUDSOPGAVE: return "Inhoudsopgave";
	case CT_BOEKINFO: return "Boekinfo";
	default: return "Component";
	}
}

void ComponentManager::UpdateInfo(Pagina *pagina)
{
	m_pPagina = pagina;
	m_pTree->clear();

	if(pagina != NULL)
	{
		enable();

		// Geef het type, x coord en y coord van elke component in de lijst weer
		int aantal = pagina->AantalComponenten();
		for(int i = 0; i < aantal; ++i)
		{
			Component *comp = pagina->GetComponent(i);

			// Set de informatie om naar een string
			QStringList info;
			info << typeToString(comp->GetType())
				<< QString("%1").arg(comp->GetPunt().x())
				<< QString("%1").arg(comp->GetPunt().y());
			// Zet deze string in de tree
			new QTreeWidgetItem(m_pTree, info);
		}
	}
	else
	{
		disable();
	}
}

int ComponentManager::getSelectedIndex() const
{
	if(m_pTree->selectedItems().isEmpty())
	{
		return -1;
	}

	// Get current selected item
	QTreeWidgetItem *item = m_pTree->currentItem();

	// Now "calculate" the index of this item, zero based.
	int index = 0;
	while(item = m_pTree->itemAbove(item))
	{
		++index;
	}

	return index;
}

void ComponentManager::wijzigComponent()
{
	assert(m_pPagina != NULL);

	int index = getSelectedIndex();
	// Show a message if no item is selected
	if(index == -1)
	{
		QMessageBox box(QMessageBox::Information, "Selectie fout", "Er is geen component geselecteerd!");
		box.exec();
		return;
	}

	// Index must be in bounds
	try
	{
		Component *comp = m_pPagina->GetComponent(index);
		emit ReqWijzigComponent(comp);
	}
	catch(C_ERROR)
	{
		qWarning("ComponentManager::wijzigComponent: Index out of bounds!");
	}
}

void ComponentManager::verwijderComponent()
{
	assert(m_pPagina != NULL);

	int index = getSelectedIndex();
	// Show a message if no item is selected
	if(index == -1)
	{
		QMessageBox box(QMessageBox::Information, "Selectie fout", "Er is geen component geselecteerd!");
		box.exec();
		return;
	}

	m_pPagina->DelComponent(index);
	UpdateInfo(m_pPagina);
	emit InfoHasChanged(m_pPagina);
}

void ComponentManager::enable()
{
	this->setEnabled(true);
}

void ComponentManager::disable()
{
	this->setEnabled(false);
}