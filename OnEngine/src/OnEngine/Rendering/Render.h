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

        void Setup();

        void Draw();

        void CleanUp();

    private:
        void Triangles();

        void TwoTriangles();

        void ThreeTriangles();

        void FourTriangles();

        void FiveTriangles();

        void BlackAndWhiteTriangles();

        void Rectangles();

        void Cube();

        void CubeFloat();
    };

}