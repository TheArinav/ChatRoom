#include <iostream>
#include "Classes/Backend/BackendComms.h"

int main() {
    Backend::BackendComms::Setup();
    Backend::BackendComms::Start();
    return 0;
}
