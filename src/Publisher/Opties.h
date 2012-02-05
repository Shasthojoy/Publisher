// Mathy Vanhoef
#ifndef OPTIES_H_
#define OPTIES_H_

#include <QFont>
#include <QObject>

/**
 *	Klasse die globale instellingen van het programma beheert. Het bied ook een functie om een dialoog te tonen
 *	om de verschillende instellingen te wijzigen. Alle members van deze klasse zijn static. Want het is niet logisch
 *	om een instatie van deze klasse te gaan maken!
 */
/*static*/ class Opties
{
public:
	static QFont m_font;
	static int m_breedte;


public:
	static QFont & GetFont() { return m_font; }
	static void SetFont(const QFont &font) { m_font = font; }
	static int GetBreedte() { return m_breedte; }
	static void SetBreedte(int breedte) { m_breedte = breedte; }
	/**
	 *	Opent get dialoog om de instellingen te veranderen
	 */
	static void OpenOptiesDialog();
};

#endif // OPTIES_H_