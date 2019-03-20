#pragma once
#include "OnEngine/Util/Defs.h"
#include "OnEngine\Objs\Objects.h"

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

        void CompileShaders();

        void SetCamera();

        void Draw();

        void CleanUp();

        /*Terrain Test*/
        int GetVerticesCount(int sWidth, int sHeight);

        int GetIndicesCount(int sWidth, int sHeight);

        float* GetVertices(int sWidth, int sHeight);

        int* GetIndices(int sWidth, int sHeight);

    private:
        void Test();
        void Test2();

        void Triangles();

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