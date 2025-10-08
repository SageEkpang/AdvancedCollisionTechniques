#ifndef BSP_TREE_H
#define BSP_TREE_H

class GameObjectEntity;

#include "Vector3.h"
#include <vector>
#include <list>

#include "ConstantBuffer.h"
#include <d3d11.h>

// NOTE: BSP (Binary Space Paritioning) Algorithm
//Select a polygon P from the list.
//Make a node N in the BSP tree, and add P to the list of polygons at that node.
//For each other polygon in the list :
//If that polygon is wholly in front of the plane containing P, move that polygon to the list of nodes in front of P.
//If that polygon is wholly behind the plane containing P, move that polygon to the list of nodes behind P.
//If that polygon is intersected by the plane containing P, split it into two polygons and move them to the respective lists of polygons behind and in front of P.
//If that polygon lies in the plane containing P, add it to the list of polygons at node N.
//Apply this algorithm to the list of polygons in front of P.
//Apply this algorithm to the list of polygons behind P.

struct BSPPlane
{
	Vector3 m_Normal;
	Vector3 m_Position;
};

struct BSPArea
{

};

struct BSPNode
{
	BSPPlane m_Plane;
	BSPNode* front;
	BSPNode* back;
	std::list<BSPArea> m_Polyhedra;
	std::list<GameObjectEntity*> m_ObjectList;
};

class BSPTree
{
private:

	BSPNode* m_HeadOfTree = nullptr;

public:

	BSPTree();
	~BSPTree();


	void BuildBSPTree(BSPNode* tree, std::list<BSPArea> polyhedra);
	void SplitPolyhedra(BSPArea* polyhedra, BSPPlane* plane, BSPNode* &front, BSPNode* &back);
	
	void Update(float deltaTime);
	void Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device);






};

#endif