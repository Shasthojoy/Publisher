// Mathy Vanhoef
#ifndef IGRAPHICS_COMPONENT_H_
#define IGRAPHICS_COMPONENT_H_

class Component;

/**
 *  Interface die elk component die moet worden voorgesteld in de scene moet implementeren.
 */
class IGraphicsComp
{
public:
	/**
	 *  Om te testen als de Graphics Component een specifieke component voorsteld
	 */
	virtual bool compare(const Component *comp) const = 0;
	/**
	 *  Geeft de component pointer terug die door de container wordt voorgesteld
	 */
	virtual Component * getComponent() const = 0;
	/**
	 *  Roept de edit dialog van de component op. Geeft true terug als ok OK werdt geklikt en er
	 *  kunnen zijn aangepast, anders false.
	 */
	virtual bool openEditDialog() = 0;
};

#endif // QGRAPHICS_COMPONENT_H_