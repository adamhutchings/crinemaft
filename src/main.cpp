#include <client/glwrapper.h>

int main(int argc, char** argv) {
    cmgl::init();
    cmgl::create_window();
    while (cmgl::window_open()) {
        cmgl::update_window();
    }
}
