#pragma once

namespace engine {

    class Time {
    public:
        Time() : dt(0.0f), lt(0.0f) {}
        ~Time() {}

        void update();

        float getDeltaTime();

    private:
        float dt;
        float lt;
    };

}
