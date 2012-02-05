#ifndef QDIALOGLAYOUTPROPERTIES_H
#define QDIALOGLAYOUTPROPERTIES_H

#include <QtGui/QDialog>
#include <QtGui/QLineEdit>

/**
 *	Dialoog voor het veranderen van de instellingen van een layout
 */
class QDialogLayoutProperties : public QDialog
{
public:
	QDialogLayoutProperties(QWidget *parent = 0, Qt::WindowFlags f = 0);
	void SetNaam(const QString &naam) { m_pNaam->setText(naam); };
	QString GetNaam() const { return m_pNaam->text(); };


private:
	QLineEdit *m_pNaam;
};

#endif // QDIALOGLAYOUTPROPERTIES_H