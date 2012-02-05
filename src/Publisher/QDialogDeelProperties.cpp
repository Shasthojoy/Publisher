#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QLabel>
#include <QtGui/QDialogButtonBox>
#include "QDialogDeelProperties.h"

QDialogDeelProperties::QDialogDeelProperties(QWidget *parent /*= 0*/, Qt::WindowFlags f /*= 0*/)
	 : QDialog(parent, f)
{
	//
	// Deel Properties
	//

	QGroupBox *boxProp = new QGroupBox("Deel Properties");
	QHBoxLayout *hboxProp = new QHBoxLayout(boxProp);

	QLabel *lblTitel = new QLabel("Titel:");
	m_pTitel = new QLineEdit();

	hboxProp->addWidget(lblTitel);
	hboxProp->addWidget(m_pTitel);

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