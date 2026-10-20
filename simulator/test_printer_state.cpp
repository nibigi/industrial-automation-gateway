
#include "printer_state.h"

#include <cassert>
#include <iostream>

int main() {
    PrinterStateMachine printer;

    assert(printer.execute("STATUS") == "STATE=IDLE\n");
    assert(printer.execute("START") == "STATE=RUNNING\n");
    assert(printer.execute("STATUS") == "STATE=RUNNING\n");

    assert(printer.execute("START") == "ERROR=INVALID_STATE\n");
    assert(printer.execute("STOP") == "STATE=IDLE\n");

    assert(printer.execute("FAULT") == "STATE=FAULT\n");
    assert(printer.execute("START") == "ERROR=INVALID_STATE\n");
    assert(printer.execute("RESET") == "STATE=IDLE\n");

    assert(printer.execute("UNKNOWN") == "ERROR=UNKNOWN_COMMAND\n");

    std::cout << "All state machine tests passed.\n";
    return 0;
}
