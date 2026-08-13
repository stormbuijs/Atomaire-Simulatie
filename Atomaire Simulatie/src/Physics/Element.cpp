#include "Physics/Element.h"


ElementData GetElementData(ElementType type)
{
	switch (type)
	{

	case ElementType::Hydrogen:
		return {
			.mass = 1.0,
			.lonePairCount = 0,
			.bondCapacity = 1
		};

	case ElementType::Oxygen:
		return {
			.mass = 16.0,
			.lonePairCount = 2,
			.bondCapacity = 2
		};

	}

	
	// Geef een "leeg" deeltje terug bij een ongeldig type
	return {
		.mass = 0.0,
		.lonePairCount = 0,
		.bondCapacity = 0
	};
}


Real GetValenceElectronCount(const ElementData& data)
{
	return static_cast<Real>(data.bondCapacity + 2 * data.lonePairCount);
}