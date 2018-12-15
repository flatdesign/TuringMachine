#include "state.h"

State::State(){

}

void State::addCommand(QString read, QString write, QString direction, QString nextState){
    this->commands[read] = new Command(read, write, direction, nextState);
}

Command *State::getCommand(QString command) {
    if(this->commands.contains(command))
        return this->commands[command];
    else
        return nullptr;
}
