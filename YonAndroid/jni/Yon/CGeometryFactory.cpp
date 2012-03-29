#include "CGeometryFactory.h"
#include "CUnit.h"
#include "SVertex.h"
#include "CEntity.h"
#include "yonMath.h"

#include "ILogger.h"

using namespace yon::core;

namespace yon{
namespace scene{

	IEntity* CGeometryFactory::createXYPlane(const core::dimension2df& size) const{
		CUnit* unit=new CUnit();

		// Create indices
		const u16 u[6] = {
			0,  2,  1,
			0,  3,  2
		};

		unit->m_indices.reallocate(6);
		for (u32 i=0; i<6; ++i)
			unit->m_indices.push(u[i]);

		//Create vertexs
		unit->m_vertices.reallocate(4);

		f32 phw,phh,mhw,mhh;
		phw=size.w/2;
		phh=size.h/2;
		mhw=phw-size.w;
		mhh=phh-size.h;

		f32 u0,u1,v0,v1;
		u0=v0=0;
		u1=v1=1;

		unit->m_vertices.push(SVertex(mhw,mhh,0,u0,v1,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(mhw,phh,0,u0,v0,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(phw,phh,0,u1,v0,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(phw,mhh,0,u1,v1,video::COLOR_WHITE));

		CEntity* entity=new CEntity();
		entity->addUnit(unit);

		unit->drop();

		return entity;

	}

	IEntity* CGeometryFactory::createCube(const core::dimension3df& size) const{

		CUnit* unit=new CUnit();

		// Create indices
		const u16 u[36] = {
			0,  2,  1,
			0,  3,  2, 
			4,  5,  6,
			4,  6,  7,
			8,  9,  10,
			8,  10, 11, 
			12, 15, 14,
			12, 14, 13, 
			16, 17, 18,
			16, 18, 19, 
			20, 23, 22,
			20, 22, 21
		};
		unit->m_indices.reallocate(36);
		for (u32 i=0; i<36; ++i)
			unit->m_indices.push(u[i]);

		//Create vertexs
		unit->m_vertices.reallocate(24);

		f32 phw,phh,phd,mhw,mhh,mhd;
		phw=size.w/2;
		phh=size.h/2;
		phd=size.d/2;
		mhw=phw-size.w;
		mhh=phh-size.h;
		mhd=phd-size.d;

		f32 u0,u1,v0,v1;
		u0=v0=0;
		u1=v1=1;

		Logger->debug("half cube size:%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",phw,phh,phd,mhw,mhh,mhd);

		unit->m_vertices.push(SVertex(mhw,mhh,mhd,u0,v1,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(mhw,mhh,phd,u0,v0,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(phw,mhh,phd,u1,v0,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(phw,mhh,mhd,u1,v1,video::COLOR_WHITE));

		unit->m_vertices.push(SVertex(mhw,phh,mhd,u0,v1,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(mhw,phh,phd,u0,v0,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(phw,phh,phd,u1,v0,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(phw,phh,mhd,u1,v1,video::COLOR_WHITE));

		unit->m_vertices.push(SVertex(mhw,mhh,mhd,u1,v0,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(mhw,phh,mhd,u1,v1,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(phw,phh,mhd,u0,v1,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(phw,mhh,mhd,u0,v0,video::COLOR_WHITE));

		unit->m_vertices.push(SVertex(mhw,mhh,phd,u0,v1,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(mhw,phh,phd,u0,v0,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(phw,phh,phd,u1,v0,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(phw,mhh,phd,u1,v1,video::COLOR_WHITE));

		//左
		unit->m_vertices.push(SVertex(mhw,mhh,mhd,u0,v0,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(mhw,mhh,phd,u1,v0,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(mhw,phh,phd,u1,v1,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(mhw,phh,mhd,u0,v1,video::COLOR_WHITE));

		//右
		unit->m_vertices.push(SVertex(phw,mhh,mhd,u1,v0,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(phw,mhh,phd,u0,v0,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(phw,phh,phd,u0,v1,video::COLOR_WHITE));
		unit->m_vertices.push(SVertex(phw,phh,mhd,u1,v1,video::COLOR_WHITE));

		CEntity* entity=new CEntity();
		entity->addUnit(unit);

		unit->drop();

		return entity;
	}
	IEntity* CGeometryFactory::createSphere(f32 radius,u32 hSteps,u32 vSteps) const{
		CUnit* unit=new CUnit();

		f32 dtheta=(float)360/hSteps;	//水平方向步增
		f32 dphi=(float)180/vSteps;		//垂直方向步增

		u32 numVertices=vSteps*hSteps<<2;
		u32 numIndices=vSteps*hSteps*6;
	
		unit->m_vertices.reallocate(numVertices);
		unit->m_indices.reallocate(numIndices);

		u32 index=0;
		//u32 index2=0;
		f32 phi=0;
		f32 theta=0;
		f32 x,y,z;
		f32 u,v;
		vector3df temp;
		for(u32 i=0;i<vSteps;++i,phi+=dphi)
		{
			for(u32 j=0;j<hSteps;++j,theta+=dtheta)
			{
				z = (f32) (radius * sinf(phi*DEGTORAD) * cosf(DEGTORAD*theta));
				x = (f32) (radius * sinf(phi*DEGTORAD) * sinf(DEGTORAD*theta));
				y = (f32) (radius * cosf(phi*DEGTORAD));
				temp.set(x,y,z);
				temp.normalize();
				u = (f32)j/hSteps;
				v = (f32)asinf(temp.y)/PI+0.5f;
				unit->m_vertices.push(SVertex(x,y,z,u,v,video::COLOR_WHITE));
				/*NORMALIZE_VERTEX_TO((*vertices)[index*3+0],(*vertices)[index*3+1],(*vertices)[index*3+2],temp);
				if(texCoords!=NULL)
				{
					(*texCoords)[index*2+0]=(float)j/hSteps;
					(*texCoords)[index*2+1]=(float)asinf(temp[1])/M_PI+0.5f;
				}
				if(normals!=NULL)
				{
					(*normals)[index*3+0]=temp[0];
					(*normals)[index*3+1]=temp[1];
					(*normals)[index*3+2]=temp[2];
				}*/
				++index;
				z = (float) (radius * sinf((phi+dphi)*DEGTORAD) * cosf(DEGTORAD*theta));
				x = (float) (radius * sinf((phi+dphi)*DEGTORAD) * sinf(DEGTORAD*theta));
				y = (float) (radius * cosf((phi+dphi)*DEGTORAD));
				temp.set(x,y,z);
				temp.normalize();
				u = (f32)j/hSteps;
				v = (f32)asinf(temp.y)/PI+0.5f;
				unit->m_vertices.push(SVertex(x,y,z,u,v,video::COLOR_WHITE));
				/*NORMALIZE_VERTEX_TO((*vertices)[index*3+0],(*vertices)[index*3+1],(*vertices)[index*3+2],temp);
				if(texCoords!=NULL)
				{
					(*texCoords)[index*2+0]=(float)j/hSteps;
					(*texCoords)[index*2+1]=(float)asinf(temp[1])/M_PI+0.5f;
				}
				if(normals!=NULL)
				{
					(*normals)[index*3+0]=temp[0];
					(*normals)[index*3+1]=temp[1];
					(*normals)[index*3+2]=temp[2];
				}*/
				++index;
				z  = (float) (radius * sinf((phi+dphi)*DEGTORAD) * cosf(DEGTORAD*(theta+dtheta)));
				x  = (float) (radius * sinf((phi+dphi)*DEGTORAD) * sinf(DEGTORAD*(theta+dtheta)));
				y  = (float) (radius * cosf((phi+dphi)*DEGTORAD));
				temp.set(x,y,z);
				temp.normalize();
				u = (f32)(j+1)/hSteps;
				v = (f32)asinf(temp.y)/PI+0.5f;
				unit->m_vertices.push(SVertex(x,y,z,u,v,video::COLOR_WHITE));
				/*NORMALIZE_VERTEX_TO((*vertices)[index*3+0],(*vertices)[index*3+1],(*vertices)[index*3+2],temp);
				if(texCoords!=NULL)
				{
					(*texCoords)[index*2+0]=(float)(j+1)/hSteps;
					(*texCoords)[index*2+1]=(float)asinf(temp[1])/M_PI+0.5f;
				}
				if(normals!=NULL)
				{
					(*normals)[index*3+0]=temp[0];
					(*normals)[index*3+1]=temp[1];
					(*normals)[index*3+2]=temp[2];
				}*/
				++index;
				z  = (float) (radius * sinf(phi*DEGTORAD) * cosf(DEGTORAD*(theta+dtheta)));
				x  = (float) (radius * sinf(phi*DEGTORAD) * sinf(DEGTORAD*(theta+dtheta)));
				y  = (float) (radius * cosf(phi*DEGTORAD));
				temp.set(x,y,z);
				temp.normalize();
				u = (f32)(j+1)/hSteps;
				v = (f32)asinf(temp.y)/PI+0.5f;
				unit->m_vertices.push(SVertex(x,y,z,u,v,video::COLOR_WHITE));
				/*NORMALIZE_VERTEX_TO((*vertices)[index*3+0],(*vertices)[index*3+1],(*vertices)[index*3+2],temp);
				if(texCoords!=NULL)
				{
					(*texCoords)[index*2+0]=(float)(j+1)/hSteps;
					(*texCoords)[index*2+1]=(float)asinf(temp[1])/M_PI+0.5f;
				}
				if(normals!=NULL)
				{
					(*normals)[index*3+0]=temp[0];
					(*normals)[index*3+1]=temp[1];
					(*normals)[index*3+2]=temp[2];
				}*/
				++index;

				unit->m_indices.push(index-4);
				unit->m_indices.push(index-3);
				unit->m_indices.push(index-2);
				unit->m_indices.push(index-4);
				unit->m_indices.push(index-2);
				unit->m_indices.push(index-1);

				/*if(indices!=NULL)
				{
					(*indices)[index2++]=index-4;
					(*indices)[index2++]=index-3;
					(*indices)[index2++]=index-2;
					(*indices)[index2++]=index-4;
					(*indices)[index2++]=index-2;
					(*indices)[index2++]=index-1;
				}*/
			}
		}

		CEntity* entity=new CEntity();
		entity->addUnit(unit);

		unit->drop();

		return entity;
	}
}//scene
}//yon