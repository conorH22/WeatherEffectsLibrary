#include "ParallaxNodeExtras.h"

//// Hack to access CCPointObject (which is not a public class)
//class PointObject : public Ref {
//	CC_SYNTHESIZE(Point, _ratio, Ratio)
//	CC_SYNTHESIZE(Point, _offset, Offset)
//	CC_SYNTHESIZE(Node*, _child, Child)	// weak ref
//};
// class PointObject  new pointobj created
class PointObject : public Ref
{
	// public method calls
public:
	static PointObject * create(Point ratio, Point offset)
	{
		PointObject *ret = new PointObject();
		ret->initWithPoint(ratio, offset);
		ret->autorelease();
		return ret;
	}

	bool initWithPoint(Point ratio, Point offset)
	{
		_ratio = ratio;
		_offset = offset;
		_child = nullptr;
		return true;
	}

	inline const Point& getRatio() const { return _ratio; };
	inline void setRatio(const Point& ratio) { _ratio = ratio; };

	inline const Point& getOffset() const { return _offset; };
	inline void setOffset(const Point& offset) { _offset = offset; };

	inline Node* getChild() const { return _child; };
	inline void setChild(Node* child) { _child = child; };
	// private  method calls
private:
	Point _ratio;
	Point _offset;
	Node *_child; // weak ref
};


// Need to provide a constructor
ParallaxNodeExtras::ParallaxNodeExtras() {
	ParallaxNode::create(); // call parent constructor
}
// pointer creates new parallaxnodeextra create method
ParallaxNodeExtras * ParallaxNodeExtras::create() {
	return new ParallaxNodeExtras();
}
// increment offset parallax array for movement of background images in level1 and 2
void ParallaxNodeExtras::incrementOffset(Point offset, Node* node){
	for (int i = 0; i < _parallaxArray->num; i++) {
		PointObject *point = (PointObject *)_parallaxArray->arr[i];
		Node * curNode = point->getChild();
		if (curNode==/*->isEqual*/(node)) {
			point->setOffset(point->getOffset() + offset);
			break;
		}
	}
}