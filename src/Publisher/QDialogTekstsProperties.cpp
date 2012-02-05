#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QPlainTextEdit>
#include <QtGui/QSpinBox>

#include "QDialogTekstsProperties.h"

QDialogTekstsProperties::QDialogTekstsProperties(QWidget *parent /*= 0*/, Qt::WindowFlags f /*= 0*/)
	: QDialogProperties(parent, f)
{
	disableHoogte();
	m_pTab->addTab(createTekstsProperties(), "Teksts");
}

QWidget * QDialogTekstsProperties::createTekstsProperties()
{
	QGroupBox *boxTeksts = new QGroupBox("Teksts");
	m_pTextEdit = new QPlainTextEdit("Typ hier uw teksts");
	QVBoxLayout *layoutTeksts = new QVBoxLayout(boxTeksts);
	layoutTeksts->addWidget(m_pTextEdit);

	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->addWidget(boxTeksts);

	QWidget *widget = new QWidget();
	widget->setLayout(vbox);

	return widget;
}

QString QDialogTekstsProperties::GetText() const
{
	return m_pTextEdit->toPlainText();
}

void QDialogTekstsProperties::SetText(const QString text)
{
	m_pTextEdit->setPlainText(text);
}