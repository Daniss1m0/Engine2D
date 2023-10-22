#include "engine.h"
using namespace std;

int main() {
    Engine engine(800, 600); //singleton
    
    if (engine.Init()) {
        engine.Run();
        engine.Deinit();
    }

    return 0;
}
