#include <assert.h>
#include <QtGui/QGroupBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QListWidget>
#include <QtGui/QPushButton>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QMessageBox>
#include "QDialogBeheerLayouts.h"
#include "QDialogLayoutProperties.h"

#include "boek.h"

QDialogBeheerLayouts::QDialogBeheerLayouts(Boek *layouts, QWidget *parent /*= 0*/, Qt::WindowFlags f /*= 0*/)
	 : QDialog(parent, f), m_pLayouts(layouts)
{
	assert(m_pLayouts != NULL);

	createWidgets();
	fillList();

	connect(m_pBtnVerwijder, SIGNAL(clicked()), this, SLOT(verwijderLayout()));
	connect(m_pBtnWijzig, SIGNAL(clicked()), this, SLOT(wijzigLayout()));
}

void QDialogBeheerLayouts::createWidgets()
{
	//
	// Beheer Layouts
	//

	QGroupBox *boxKies = new QGroupBox("Beheer Layouts");
	QVBoxLayout *hboxKies = new QVBoxLayout(boxKies);

	// Lijst layouts
	m_pListLayout = new QListWidget();

	// Buttons
	m_pBtnVerwijder = new QPushButton("Verwijder");
	m_pBtnWijzig = new QPushButton("Wijzig");
	QHBoxLayout *vboxBtn = new QHBoxLayout();
	vboxBtn->addWidget(m_pBtnVerwijder);
	vboxBtn->addWidget(m_pBtnWijzig);

	hboxKies->addWidget(m_pListLayout);
	hboxKies->addLayout(vboxBtn);

	//
	// ButtonBox
	//

	QDialogButtonBox *buttonBox = new QDialogButtonBox();
	buttonBox->setOrientation(Qt::Horizontal);
	buttonBox->setStandardButtons(QDialogButtonBox::Ok);
	QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(boxKies);
	mainLayout->addWidget(buttonBox);

	setLayout(mainLayout);
}

void QDialogBeheerLayouts::fillList()
{
	int aantalDelen = m_pLayouts->AantalDelen();

	m_pListLayout->clear();

	// Voeg de de naam van elke layout toe aan de lijst
	for(int i = 0; i < aantalDelen; ++i)
	{
		Deel *deel = m_pLayouts->GetDeel(i);
		m_pListLayout->insertItem(i + 1, QString::fromStdString(deel->GetTitel()));
	}
}

bool QDialogBeheerLayouts::getSelectedIndex(int *index) const
{
	*index = m_pListLayout->currentRow();

	if(m_pListLayout->selectedItems().size() <= 0)
	{
		return false;
	}

	return true;
}

void QDialogBeheerLayouts::verwijderLayout()
{
	int index;

	if(getSelectedIndex(&index))
	{
		m_pLayouts->DelDeel(index);
		fillList();
	}
	else
	{
		QMessageBox box(QMessageBox::Information, "Selectie fout", "Er is geen layout geselecteerd!");
		box.exec();
		return;
	}
}

void QDialogBeheerLayouts::wijzigLayout()
{
	int index;

	if(getSelectedIndex(&index))
	{
		Deel *deel = m_pLayouts->GetDeel(index);

		QDialogLayoutProperties dialog;
		dialog.SetNaam(QString::fromStdString(deel->GetTitel()));

		if(dialog.exec())
		{
			deel->SetTitel(dialog.GetNaam().toStdString());
			fillList();
		}
	}
	else
	{
		QMessageBox box(QMessageBox::Information, "Selectie fout", "Er is geen layout geselecteerd!");
		box.exec();
		return;
	}
}