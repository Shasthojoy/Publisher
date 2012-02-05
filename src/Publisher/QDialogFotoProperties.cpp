#include <QtGui/QGroupBox>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QTabWidget>
#include <QtGui/QPushButton>
#include <QtGui/QFileDialog>
#include <QtGui/QSpinBox>

#include "QDialogFotoProperties.h"

QDialogFotoProperties::QDialogFotoProperties(QWidget *parent /*= 0*/, Qt::WindowFlags f /*= 0*/)
	: QDialogProperties(parent, f)
{
	disableHoogte();
	m_pSpinBreedte->setEnabled(false);
	m_pTab->addTab(createFotoProperties(), "Foto");
}

QWidget * QDialogFotoProperties::createFotoProperties()
{
	// Beschrijving

	QGroupBox *boxBeschr = new QGroupBox("Beschrijving");
	m_pBeschr = new QLineEdit("Dit is een foto!");
	QVBoxLayout *layoutBeschr = new QVBoxLayout(boxBeschr);
	layoutBeschr->addWidget(m_pBeschr);

	// Locatie

	QGroupBox *boxFoto = new QGroupBox("Locatie");
	m_pLocatie = new QLineEdit("C:\\");
	m_pLocatie->setMinimumWidth(300);
	
	QPushButton *btnBrowse = new QPushButton("Browse");
	QObject::connect(btnBrowse, SIGNAL(clicked()), this, SLOT(getNewLocation()));

	QVBoxLayout *layoutFoto = new QVBoxLayout(boxFoto);
	layoutFoto->addWidget(m_pLocatie);
	layoutFoto->addWidget(btnBrowse, 0, Qt::AlignRight);

	// Zet dit in een widget om te gebruiken een in tab

	QVBoxLayout *vbox = new QVBoxLayout();
	vbox->addWidget(boxBeschr, 0, Qt::AlignTop);
	vbox->addWidget(boxFoto, 0, Qt::AlignTop);

	QWidget *widget = new QWidget();
	widget->setLayout(vbox);

	// En geef deze widget nu terug

	return widget;
}

void QDialogFotoProperties::getNewLocation()
{
	QFileDialog fileDialog;
	fileDialog.setFileMode(QFileDialog::ExistingFile);

	QStringList filters;
	filters << "Images (*.bmp *.gif *.jpg *jpeg *png *xpm)"
		<< "Any files (*)";
	fileDialog.setNameFilters(filters);

	if(fileDialog.exec())
	{
		QStringList files = fileDialog.selectedFiles();
		if(files.size() >= 1)
		{
			m_pLocatie->setText(files.first());
		}
		else
		{
			qWarning("No files selected in QFileDialog but user still managed to click open?");
		}
	}
}

void QDialogFotoProperties::SetLocatie(const QString &loc)
{
	m_pLocatie->setText(loc);
}

void QDialogFotoProperties::SetBeschrijving(const QString &beschr)
{
	m_pBeschr->setText(beschr);
}

QString QDialogFotoProperties::GetLocatie() const
{
	return m_pLocatie->text();
}

QString QDialogFotoProperties::GetBeschrijving() const
{
	return m_pBeschr->text();
}