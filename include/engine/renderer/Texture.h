#pragma once

namespace engine {

    class Texture {
    public:
        Texture();
        ~Texture();

        bool init(const char* path);
        void bind(unsigned int slot = 0);

        int getWidth();
        int getHeight();

    private:
        unsigned int id;
        int width;
        int height;
        int channels;
    };

}