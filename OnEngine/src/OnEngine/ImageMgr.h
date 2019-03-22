#pragma once
#include "OnEngine\Util\Defs.h"
#include <glad\glad.h>

namespace on
{

    class ON_API ImageMgr
    {
    private:
        int m_ImageWith;
        int m_ImageHeight;
        unsigned char* m_Image;

        GLuint m_TextureID;
        //GLuint texture0;

    public:

        ImageMgr();
        ~ImageMgr();

        void Init();
        GLuint GetextureID() { return m_TextureID; }
        void LoadTexture(const char* filePath);
        void LoadTexture(const char* filePath, int width, int height);

        void GenerateTexture();
        void GenerateTexture(GLuint& textureID);

        void GenTexture(unsigned char* LoadTexture(const char* filePath));
        void GenTexture(const char* filePath);
        void GenTexture(const char* filePath, GLuint& texture);

    };

}

