// Mathy Vanhoef
#ifndef COMPONENT_LIST_H_
#define COMPONENT_LIST_H_

#include <QtGui/QListWidget>

/**
 *  Widget waarin men iconen van componenten kan plaatsen. Hiermee kan de gebruiker m.b.v. drag en drop
 *  dit component op de scene slepen om zo component toe te voegen.
 *
 *	Data structure of drag and drop operation:
 *						Data			Storage location in QListWidgetItem data element
 *						----			----------------
 *		First object:	ComponentType	UserRole
 *		Second object:	arg2			UserRole + 1
 *	This way the receiving widget will know what component got selected in
 *	the list (UserRole), and you can give an argument to describe more "special"
 *	components (UserRole + 1) (like lists with bullets or lists with numbers).
 */
class ComponentList : public QListWidget
{
public:
	ComponentList(QWidget *parent = 0);


protected:
	/*virtual*/ void startDrag(Qt::DropActions supportedActions);


private:
	/**
	 *  Hoogte van de iconen de een component voorstellen
	 */
	static const int ICON_HEIGHT;
	/**
	 *  Breedte van de iconen de een component voorstellen
	 */
	static const int ICON_WIDTH;
	/**
	 *  Vult de lijst met component die de gebruiker m.b.v. drag en drop op de scene kan plaatsen
	 */
	void insertDefaultComponents();
};

#endif // COMPONENT_LIST_H_