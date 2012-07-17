#include "vector3dTestCase.h"
#include <Windows.h>

CPPUNIT_TEST_SUITE_REGISTRATION( vector3dTestCase );

void vector3dTestCase::setUp()
{
}
void vector3dTestCase::getHorizontalAngle(){
	core::vector3df v;
	core::matrix4f m;
	core::vector3df o;

	v.set(1,0,0);
	printf("\n%.2f,%.2f\n",v.getHorizontalAngle().x,v.getHorizontalAngle().y);
	CPPUNIT_ASSERT(core::equals(v.getHorizontalAngle().x,0.0f,0.001f));
	CPPUNIT_ASSERT(core::equals(v.getHorizontalAngle().y,0.0f,0.001f));

	o.set(1,0,0);
	m.makeIdentity();
	m.setRotationDegrees(v.getHorizontalAngle());
	m.transformVect(o);
	printf("%.2f,%.2f,%.2f\n",o.x,o.y,o.z);

	v.set(0,1,0);
	printf("\n%.2f,%.2f\n",v.getHorizontalAngle().x,v.getHorizontalAngle().y);
	CPPUNIT_ASSERT(core::equals(v.getHorizontalAngle().x,90.0f,0.001f));
	CPPUNIT_ASSERT(core::equals(v.getHorizontalAngle().y,270.0f,0.001f));

	o.set(0,270,0);
	m.makeIdentity();
	m.setRotationDegrees(v);
	m.transformVect(o);
	printf("%.2f,%.2f,%.2f\n",o.x,o.y,o.z);

	v.set(0,0,1);
	printf("\n%.2f,%.2f\n",v.getHorizontalAngle().x,v.getHorizontalAngle().y);
	CPPUNIT_ASSERT(core::equals(v.getHorizontalAngle().x,0.0f,0.001f));
	CPPUNIT_ASSERT(core::equals(v.getHorizontalAngle().y,270.0f,0.001f));

	o.set(1,0,0);
	m.makeIdentity();
	m.setRotationDegrees(v.getHorizontalAngle());
	m.transformVect(o);
	printf("%.2f,%.2f,%.2f\n",o.x,o.y,o.z);

	

	v.set(-10,0,0);
	printf("\n%.2f,%.2f\n",v.getHorizontalAngle().x,v.getHorizontalAngle().y);
	CPPUNIT_ASSERT(core::equals(v.getHorizontalAngle().x,0.0f,0.001f));
	CPPUNIT_ASSERT(core::equals(v.getHorizontalAngle().y,180.0f,0.001f));

	v.set(0,-1,0);
	printf("\n%.2f,%.2f\n",v.getHorizontalAngle().x,v.getHorizontalAngle().y);
	CPPUNIT_ASSERT(core::equals(v.getHorizontalAngle().x,-90.0f,0.001f));
	CPPUNIT_ASSERT(core::equals(v.getHorizontalAngle().y,270.0f,0.001f));

}