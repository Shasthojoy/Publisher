#include <QtGui/QVBoxLayout>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QPushButton>
#include <QtGui/QTabWidget>
#include <QtGui/QFontDialog>

#include "QDialogProperties.h"

QDialogProperties::QDialogProperties(QWidget *parent /*= 0*/, Qt::WindowFlags f /*= 0*/) : QDialog(parent, f)
{
	m_pTab = new QTabWidget();

	QWidget *pageOne = createDefaultProperties();

	// 1 - Create default tab

	m_pTab->addTab(pageOne, "Algemeen");

	// 2 - Create OK and CANCEL buttons

	QDialogButtonBox *buttonBox = new QDialogButtonBox();
	buttonBox->setOrientation(Qt::Horizontal);
	buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
	QObject::connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    QObject::connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

	// 3 - Put this in the dialog

	QVBoxLayout *vbar = new QVBoxLayout();
	vbar->addWidget(m_pTab);
	vbar->addWidget(buttonBox);

	setLayout(vbar);
}

QGroupBox * QDialogProperties::createDefaultPropertiesBox(QSpinBox * &spinBoxEen, QSpinBox * &spinBoxTwee,
	const char *titel, const char *naamEen, const char *naamTwee)
{
	QGroupBox *box = new QGroupBox(titel);
	QGridLayout *gridPos = new QGridLayout(box);

	QLabel *lblX = new QLabel(naamEen);
	QLabel *lblY = new QLabel(naamTwee);
	spinBoxEen = new QSpinBox();
	spinBoxEen->setRange(0, 999);
	spinBoxTwee = new QSpinBox();
	spinBoxTwee->setRange(0, 999);

	gridPos->addWidget(lblX, 0, 0);
	gridPos->addWidget(lblY, 1, 0);
	gridPos->addWidget(spinBoxEen, 0, 1);
	gridPos->addWidget(spinBoxTwee, 1, 1);

	return box;
}

QWidget * QDialogProperties::createDefaultProperties()
{
	//
	// 1 - Maak spinboxes voor het editeren van de positie en grootte
	//

	QGroupBox *boxPos = createDefaultPropertiesBox(m_pSpinX, m_pSpinY, "Positie", "X:", "Y:");
	QGroupBox *boxSize = createDefaultPropertiesBox(m_pSpinHoogte, m_pSpinBreedte, "Grootte", "Hoogte:", "Breedte:");

	QGroupBox *boxFont = new QGroupBox("Lettertype");
	QVBoxLayout *vboxFont = new QVBoxLayout(boxFont);

	//
	// 2 - Voor het instellen van het font
	//
	// Gebruik SetFont na het aanmaken van en QDialogProperties object om een correcte default
	// font in the stellen!
	m_pLblFont = new QLabel("Times new roman 16");
	QPushButton *changeFont = new QPushButton("Verander Lettertype");
	QObject::connect(changeFont, SIGNAL(clicked()), this, SLOT(getNewFont()));

	vboxFont->addWidget(m_pLblFont);
	vboxFont->addWidget(changeFont, 0, Qt::AlignRight);

	//
	// 3 - Zet dit allemaal in een mooie layout
	//
	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->addWidget(boxPos);
	vbox->addWidget(boxSize);
	vbox->addWidget(boxFont);

	//
	// 4 - Geeft een widget met deze layout terug
	//

	QWidget *widget = new QWidget();
	widget->setLayout(vbox);

	return widget;
}

void QDialogProperties::getNewFont()
{
	bool ok;
	QFont font = QFontDialog::getFont(&ok, m_font, this);

	if(ok) {
		SetFont(font);
	}
}

void QDialogProperties::SetPos(const QPoint &pos)
{
	m_pSpinX->setValue(pos.x());
	m_pSpinY->setValue(pos.y());
}

void QDialogProperties::SetSize(const QSize &size)
{
	m_pSpinHoogte->setValue(size.height());
	m_pSpinBreedte->setValue(size.width());
}

void QDialogProperties::SetFont(const QFont &font)
{
	this->m_font = font;
	this->m_pLblFont->setText(font.family() + " (" + QString::number(font.pointSize()) + ")");
	m_pLblFont->setFont(font);
}

QPoint QDialogProperties::GetPos() const
{
	return QPoint(m_pSpinX->value(), m_pSpinY->value());
}

QSize QDialogProperties::GetSize() const
{
	return QSize(m_pSpinBreedte->value(), m_pSpinHoogte->value());
}

QFont QDialogProperties::GetFont() const
{
	return m_font;
}

void QDialogProperties::disableHoogte()
{
	m_pSpinHoogte->setEnabled(false);
}