#include "Opties.h"
#include "OptiesDialog.h"

// Stel standaard instellingen in
QFont Opties::m_font = QFont();
int Opties::m_breedte = 200;

void Opties::OpenOptiesDialog()
{
	OptiesDialog dialog;

	dialog.SetFont(m_font);
	dialog.SetBreedte(m_breedte);

	if(dialog.exec())
	{
		m_font = dialog.GetFont();
		m_breedte = dialog.GetBreedte();
	}
}