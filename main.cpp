#include "config.h"
#include "file_processor.h"

int main() {
    auto config = SetConfig();
    FileProcessor file_processor(config);
    file_processor.Run();
}
