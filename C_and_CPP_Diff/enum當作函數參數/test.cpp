#include <iostream>
using namespace std;

enum _MIKEY_ {
    Valid = 0,
    Pass,
    Fail
};

int DecoderH264(_MIKEY_ key_type, int key_content, int key_value) {
    cout << key_type << endl;
    return 0;
}

int main(int argc, char* argv[]) {
    DecoderH264(Pass, 0, 0);
    return 0;
}
