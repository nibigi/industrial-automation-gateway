
#pragma once

#include <string>

enum class PrinterState {
    IDLE,
    RUNNING,
    FAULT
};

class PrinterStateMachine {
public:
    std::string execute(const std::string& command) {
        if (command == "STATUS") {
            return "STATE=" + stateName() + "\n";
        }

        if (command == "START" && state_ == PrinterState::IDLE) {
            state_ = PrinterState::RUNNING;
            return "STATE=RUNNING\n";
        }

        if (command == "STOP" && state_ == PrinterState::RUNNING) {
            state_ = PrinterState::IDLE;
            return "STATE=IDLE\n";
        }

        if (command == "FAULT" && state_ != PrinterState::FAULT) {
            state_ = PrinterState::FAULT;
            return "STATE=FAULT\n";
        }

        if (command == "RESET" && state_ == PrinterState::FAULT) {
            state_ = PrinterState::IDLE;
            return "STATE=IDLE\n";
        }

        if (command == "START" || command == "STOP" ||
            command == "FAULT" || command == "RESET") {
            return "ERROR=INVALID_STATE\n";
        }

        return "ERROR=UNKNOWN_COMMAND\n";
    }

private:
    PrinterState state_ = PrinterState::IDLE;

    std::string stateName() const {
        switch (state_) {
            case PrinterState::IDLE:    return "IDLE";
            case PrinterState::RUNNING: return "RUNNING";
            case PrinterState::FAULT:   return "FAULT";
        }
        return "UNKNOWN";
    }
};
