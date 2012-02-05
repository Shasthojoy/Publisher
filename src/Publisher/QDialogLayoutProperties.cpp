#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QLabel>
#include <QtGui/QDialogButtonBox>
#include "QDialogLayoutProperties.h"

QDialogLayoutProperties::QDialogLayoutProperties(QWidget *parent /*= 0*/, Qt::WindowFlags f /*= 0*/)
	 : QDialog(parent, f)
{
	//
	// Deel Properties
	//

	QGroupBox *boxProp = new QGroupBox("Layout Properties");
	QHBoxLayout *hboxProp = new QHBoxLayout(boxProp);

	QLabel *lblNaam = new QLabel("Naam Layout:");
	m_pNaam = new QLineEdit();

	hboxProp->addWidget(lblNaam);
	hboxProp->addWidget(m_pNaam);

	//
	// ButtonBox
	//

	QDialogButtonBox *buttonBox = new QDialogButtonBox();
	buttonBox->setOrientation(Qt::Horizontal);
	buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
	QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(boxProp);
	mainLayout->addWidget(buttonBox);

	setLayout(mainLayout);
}