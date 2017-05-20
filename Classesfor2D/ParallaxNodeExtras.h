#ifndef _PARALLAX_NODE_EXTRAS_
#define _PARALLAX_NODE_EXTRAS_

#include "cocos2d.h"

USING_NS_CC;
// class parallaxNodeExtra for parallax scrolling background class method defintions and variables

class ParallaxNodeExtras : public ParallaxNode {

public:

	// constructor
	ParallaxNodeExtras();

	// just to avoid ugly later cast and also for safety
	static ParallaxNodeExtras * create();

	// Facility method
	void incrementOffset(Point offset, Node* node);
};

#endif // _PARALLAX_NODE_EXTRAS_
