#pragma once
#include "OnEngine/Util/Defs.h"
#include "OnEngine\Objs\Objects.h"
#include "OnEngine\Drawing\Primitive.h"


namespace on
{

    class ON_API Render : public Objects
    {
    private:
        /*Getting The Objts*/
        Objects m_Obj;

    public:
        Render();
        ~Render();

        void Init();

        void InitPrimitiveVAO(Primitive* primitive);

        void InitVAO(Primitive * primitive);


        void CompileShaders();

        void SetCamera();

        void Draw();

        void CleanUp();

        /*Terrain Test*/
        int GetVerticesCount(int sWidth, int sHeight);

        int GetIndicesCount(int sWidth, int sHeight);

        float* GetVertices(int sWidth, int sHeight);

        int* GetIndices(int sWidth, int sHeight);

        void TriangleTwo();

    private:
        void Test();
        void Test2();

        void DQuad();

        void Triangles();

        void TriangleOne();

        

        void PrimitiveTriangles();

        void TwoTriangles();

        void ThreeTriangles();

        void FourTriangles();

        void FiveTriangles();

        void BlackAndWhiteTriangles();

        void Rectangles();

        void Cube();

        void CubeColor();

        void CubeFloat();

        void Terrain();
    };

}