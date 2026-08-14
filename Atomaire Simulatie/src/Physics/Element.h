#pragma once

#include "Math/Real.h"


enum class ElementType
{
	Hydrogen,
	Oxygen,
	Carbon
};


struct ElementData
{
	Real mass;
	
	int lonePairCount;
	int bondCapacity;
};


ElementData GetElementData(ElementType type);


Real GetValenceElectronCount(const ElementData& data);