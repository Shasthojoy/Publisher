#include <assert.h>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QVBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QComboBox>
#include <QtGui/QDialogButtonBox>
#include "QDialogKiesLayout.h"
#include "boek.h"

QDialogKiesLayout::QDialogKiesLayout(Boek *layouts, QWidget *parent /*= 0*/, Qt::WindowFlags f /*= 0*/)
	 : QDialog(parent, f), m_pLayouts(layouts)
{
	assert(layouts != NULL);

	createWidgets();
	fillComboBox();
}

Pagina * QDialogKiesLayout::getSelectedLayout() const
{
	int index = m_pCmbLayout->currentIndex();

	if(index == -1)
	{
		qWarning("No index selected in QDialogKiesLayout ?!");
		return NULL;
	}

	Deel *deel = m_pLayouts->GetDeel(index);
	return deel->GetPagina(0);
}

void QDialogKiesLayout::fillComboBox()
{
	int aantalDelen = m_pLayouts->AantalDelen();

	for(int i = 0; i < aantalDelen; ++i)
	{
		Deel *deel = m_pLayouts->GetDeel(i);
		m_pCmbLayout->insertItem(i + 1, QString::fromStdString(deel->GetTitel()));
	}
}

void QDialogKiesLayout::createWidgets()
{
	//
	// Deel Properties
	//

	QGroupBox *boxKies = new QGroupBox("Kies Layout");
	QHBoxLayout *hboxKies = new QHBoxLayout(boxKies);

	QLabel *lblLayout = new QLabel("Layout:");
	m_pCmbLayout = new QComboBox();

	hboxKies->addWidget(lblLayout);
	hboxKies->addWidget(m_pCmbLayout);

	//
	// ButtonBox
	//

	QDialogButtonBox *buttonBox = new QDialogButtonBox();
	buttonBox->setOrientation(Qt::Horizontal);
	buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
	QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(boxKies);
	mainLayout->addWidget(buttonBox);

	setLayout(mainLayout);
}