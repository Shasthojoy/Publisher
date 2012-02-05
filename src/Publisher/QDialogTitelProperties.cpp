#include <QtGui/QTabWidget>
#include <QtGui/QGroupBox>
#include <QtGui/QCheckBox>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QSpinBox>

#include "QDialogTitelProperties.h"

QDialogTitelProperties::QDialogTitelProperties(QWidget *parent /*= 0*/, Qt::WindowFlags f /*= 0*/)
	 : QDialogProperties(parent, f)
{
	disableHoogte();
	m_pSpinBreedte->setEnabled(false);
	m_pTab->addTab(createTitelProperties(), "Titel");
}

QWidget * QDialogTitelProperties::createTitelProperties()
{
	QGroupBox *boxTitel = new QGroupBox("Titel");
	m_pDeelTitel = new QCheckBox("Deel Titel");
	QObject::connect(m_pDeelTitel, SIGNAL(toggled(bool)), this, SLOT(setCheckboxState(bool)));

	m_pTitel = new QLineEdit();

	QVBoxLayout *layoutTitel = new QVBoxLayout(boxTitel);
	layoutTitel->addWidget(m_pDeelTitel);
	layoutTitel->addWidget(m_pTitel);

	QVBoxLayout *layout = new QVBoxLayout();
	layout->addWidget(boxTitel, 0, Qt::AlignTop);
	QWidget *widget = new QWidget();
	widget->setLayout(layout);

	return widget;
}

void QDialogTitelProperties::setCheckboxState(bool state)
{
	m_pTitel->setEnabled(!state);
}

QString QDialogTitelProperties::GetTitel() const
{
	return m_pTitel->text();
}

bool QDialogTitelProperties::GetDeelTitel() const
{
	return m_pDeelTitel->checkState() == Qt::Checked;
}

void QDialogTitelProperties::SetTitel(const QString &titel)
{
	m_pTitel->setText(titel);
}

void QDialogTitelProperties::SetDeelTitel(bool isDeelTitel)
{
	m_pDeelTitel->setCheckState(isDeelTitel ? Qt::Checked : Qt::Unchecked);
}