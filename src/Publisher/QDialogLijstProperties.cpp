#include <string>
#include <QtGui/QTabWidget>
#include <QtGui/QGroupBox>
#include <QtGui/QComboBox>
#include <QtGui/QLabel>
#include <QtGui/QHBoxLayout>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QTextBlock>
#include <QtGui/QSpinBox>
using std::string;

#include "QDialogLijstProperties.h"

QDialogLijstProperties::QDialogLijstProperties(QWidget *parent /*= 0*/, Qt::WindowFlags f /*= 0*/)
	: QDialogProperties(parent, f)
{
	m_pSpinHoogte->setEnabled(false);
	m_pTab->addTab(createLijstProperties(), "Lijst");
}

QWidget * QDialogLijstProperties::createLijstProperties()
{
	QGroupBox *boxLijst = new QGroupBox("Lijst");
	QLabel *lblType = new QLabel("Type");
	m_pLijstType = new QComboBox();
	m_pLijstType->insertItem(0, "Nummers");
	m_pLijstType->insertItem(1, "Punten");
	QHBoxLayout *layoutLijst = new QHBoxLayout(boxLijst);
	layoutLijst->addWidget(lblType);
	layoutLijst->addWidget(m_pLijstType);
	
	QGroupBox *boxItems = new QGroupBox();
	QLabel *lblInfo = new QLabel("Elke regel is een item!");
	m_pItems = new QPlainTextEdit();
	QVBoxLayout *layoutItems = new QVBoxLayout(boxItems);
	layoutItems->addWidget(lblInfo, 0, Qt::AlignCenter);
	layoutItems->addWidget(m_pItems);

	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->addWidget(boxLijst);
	vbox->addWidget(boxItems);

	QWidget *widget = new QWidget();
	widget->setLayout(vbox);

	return widget;
}

LijstType QDialogLijstProperties::GetLijstType() const
{
	switch(m_pLijstType->currentIndex())
	{
	case 0:
		return LT_NUMMERS;

	case 1:
		return LT_PUNTEN;

	default:
		qWarning("Invalid selection in combo box!");
		return LT_NUMMERS;
	}
}

list<string> QDialogLijstProperties::GetItems() const
{
	list<string> items;
	
	QTextDocument *teksts = m_pItems->document();

	for(QTextBlock it = teksts->begin(); it != teksts->end(); it = it.next())
	{
		items.push_back(it.text().toStdString());
	}

	return items;
}

void QDialogLijstProperties::SetLijstType(LijstType type)
{
	switch(type)
	{
	case LT_NUMMERS:
		m_pLijstType->setCurrentIndex(0);
		break;

	case LT_PUNTEN:
		m_pLijstType->setCurrentIndex(1);
		break;

	default:
		qWarning("Unexpected LijstType in SetLijstType!");
	}
}

void QDialogLijstProperties::SetItems(const QString &items)
{
	m_pItems->setPlainText(items);
}