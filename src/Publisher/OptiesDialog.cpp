#include <QtGui/QGroupBox>
#include <QtGui/QLabel>
#include <QtGui/QVBoxLayout>
#include <QtGui/QPushButton>
#include <QtGui/QSpinBox>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFontDialog>

#include "OptiesDialog.h"

OptiesDialog::OptiesDialog(QWidget *parent /*= 0*/, Qt::WindowFlags f /*= 0*/)
	 : QDialog(parent, f)
{
	//
	// 1 - Font
	//

	QGroupBox *boxFont = new QGroupBox("Standaard Lettertype");
	QVBoxLayout *vboxFont = new QVBoxLayout(boxFont);

	// Actual font has to be set with the Set Functions!
	m_pLblFont = new QLabel("Times new roman 16");
	QPushButton *changeFont = new QPushButton("Verander Lettertype");
	QObject::connect(changeFont, SIGNAL(clicked()), this, SLOT(getNewFont()));

	vboxFont->addWidget(m_pLblFont);
	vboxFont->addWidget(changeFont, 0, Qt::AlignRight);

	//
	// 2 - Waarden
	//

	QGroupBox *boxWaarden = new QGroupBox("Standaard Waarden");

	// Breedte
	QLabel *lblBreedte = new QLabel("Breedte Nieuw Component");
	m_pSpinBreedte = new QSpinBox();
	m_pSpinBreedte->setRange(0, 1000);
	
	QGridLayout *gridWaarden = new QGridLayout(boxWaarden);
	gridWaarden->addWidget(lblBreedte, 0, 0);
	gridWaarden->addWidget(m_pSpinBreedte, 0, 1);

	//
	// 3 - Buttonbox
	//

	QDialogButtonBox *buttonBox = new QDialogButtonBox();
	buttonBox->setOrientation(Qt::Horizontal);
	buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
	QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));


	//
	// 4 - Put it all in a layout
	//

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addWidget(boxFont);
	mainLayout->addWidget(boxWaarden);
	mainLayout->addWidget(buttonBox);
	setLayout(mainLayout);
}

void OptiesDialog::SetFont(const QFont &font)
{
	m_font = font;
	m_pLblFont->setText(font.family() + " (" + QString::number(font.pointSize()) + ")");
	m_pLblFont->setFont(font);
}

void OptiesDialog::getNewFont()
{
	bool ok;
	QFont font = QFontDialog::getFont(&ok, m_font, this);

	if(ok) {
		SetFont(font);
	}
}