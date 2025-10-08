#include "BSPTree.h"

BSPTree::BSPTree()
{


}

BSPTree::~BSPTree()
{


}

void BSPTree::BuildBSPTree(BSPNode* tree, std::list<BSPArea> polyhedra)
{
   /* polygon* root = polygons.Get_From_List();
    tree->partition = root->Get_Plane();
    tree->polygons.Add_To_List(root);
    list      front_list,
        back_list;
    polygon* poly;
    while ((poly = polygons.Get_From_List()) != 0)
    {
        int   result = tree->partition.Classify_Polygon(poly);
        switch (result)
        {
        case COINCIDENT:
            tree->polygons.Add_To_List(poly);
            break;
        case IN_BACK_OF:
            back_list.Add_To_List(poly);
            break;
        case IN_FRONT_OF:
            front_list.Add_To_List(poly);
            break;
        case SPANNING:
            polygon* front_piece, * back_piece;
            Split_Polygon(poly, tree->partition, front_piece, back_piece);
            back_list.Add_To_List(back_piece);
            front_list.Add_To_List(front_piece);
            break;
        }
    }
    if (!front_list.Is_Empty_List())
    {
        tree->front = new BSP_tree;
        Build_BSP_Tree(tree->front, front_list);
    }
    if (!back_list.Is_Empty_List())
    {
        tree->back = new BSP_tree;
        Build_BSP_Tree(tree->back, back_list);
    }*/
}

void BSPTree::SplitPolyhedra(BSPArea* polyhedra, BSPPlane* plane, BSPNode*& front, BSPNode*& back)
{
    //int   count = poly->NumVertices(),
    //    out_c = 0, in_c = 0;
    //point ptA, ptB,
    //    outpts[MAXPTS],
    //    inpts[MAXPTS];
    //real	sideA, sideB;
    //ptA = poly->Vertex(count - 1);
    //sideA = part->Classify_Point(ptA);
    //for (short i = -1; ++i < count;)
    //{
    //    ptB = poly->Vertex(i);
    //    sideB = part->Classify_Point(ptB);
    //    if (sideB > 0)
    //    {
    //        if (sideA < 0)
    //        {
    //            // compute the intersection point of the line
    //            // from point A to point B with the partition
    //            // plane. This is a simple ray-plane intersection.
    //            vector v = ptB - ptA;
    //            real   sect = -part->Classify_Point(ptA) / (part->Normal() | v);
    //            outpts[out_c++] = inpts[in_c++] = ptA + (v * sect);
    //        }
    //        outpts[out_c++] = ptB;
    //    }
    //    else if (sideB < 0)
    //    {
    //        if (sideA > 0)
    //        {
    //            // compute the intersection point of the line
    //            // from point A to point B with the partition
    //            // plane. This is a simple ray-plane intersection.
    //            vector v = ptB - ptA;
    //            real   sect = -part->Classify_Point(ptA) / (part->Normal() | v);
    //            outpts[out_c++] = inpts[in_c++] = ptA + (v * sect);
    //        }
    //        inpts[in_c++] = ptB;
    //    }
    //    else
    //        outpts[out_c++] = inpts[in_c++] = ptB;
    //    ptA = ptB;
    //    sideA = sideB;
    //}
    //front = new polygon(outpts, out_c);
    //back = new polygon(inpts, in_c);






}

void BSPTree::Update(float deltaTime)
{

}

void BSPTree::Draw(ConstantBuffer constantBufferData, ID3D11Buffer* constBuff, ID3D11DeviceContext* pImmediateContext, ID3D11Device* device)
{
    //real   result = tree->partition.Classify_Point(eye);
    //if (result > 0)
    //{
    //    Draw_BSP_Tree(tree->back, eye);
    //    tree->polygons.Draw_Polygon_List();
    //    Draw_BSP_Tree(tree->front, eye);
    //}
    //else if (result < 0)
    //{
    //    Draw_BSP_Tree(tree->front, eye);
    //    tree->polygons.Draw_Polygon_List();
    //    Draw_BSP_Tree(tree->back, eye);
    //}
    //else // result is 0
    //{
    //    // the eye point is on the partition plane...
    //    Draw_BSP_Tree(tree->front, eye);
    //    Draw_BSP_Tree(tree->back, eye);
    //}


}