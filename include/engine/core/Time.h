#pragma once

namespace engine {

    class Time {
    public:
        Time();
        ~Time();

        void update();

        float getDeltaTime();

    private:
        float dt;
        float lt;
    };

}
