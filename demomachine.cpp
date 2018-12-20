#include "demomachine.h"
#include "qdebug.h"



DemoMachine::DemoMachine(int tapes) {
    for(int i = 0; i < tapes; i++) {
        this->lines.push_back("_");
        this->positions.push_back(0);
    }
}

void DemoMachine::runAlgorithm() {
    QVector<int> stepsArray;
    QVector<QString> words = this->combinations(this->length);
    int progress;
    for(int i = 0; i < words.size(); i++) {
        this->currentWord = words[i];
        this->start();
        stepsArray.push_back(this->steps);
        this->reset();
        progress = (int)((i + 1)/words.size() * 100);
        emit this->upProgress(progress, this->progress);
    }
    words.clear();

    double max = 0;
    for(int i = 0; i < stepsArray.size(); i++) {
        if(stepsArray[i] > max)
            max = stepsArray[i];
    }

    emit this->print(this->length, max, this->plot);
    emit this->stop();
}


void DemoMachine::start() {
    bool key;
    do {
      key = this->step();
    } while (key);
}


bool DemoMachine::step() {

    if(this->steps == 0) {
        this->lines[0] = this->currentWord;
    }

    QString value;
    for(int i = 0; i < this->lines.size(); i++) {         // Считали команду
        value += this->lines[i][this->positions[i]];
    }

    Command *command = this->states[this->state]->getCommand(value);
    if(command == nullptr)
        return false;

    value = command->getWrite();                    // Получили команду

    for(int i = 0; i < this->lines.size(); i++) {         // Записали нужные сиволы в строки
        this->lines[i][this->positions[i]] = value[i];
    }

    QString key = command->getDirection();      // Меням позицию
    for(int i = 0; i < lines.size(); i++) {
        switch(key[i].unicode()) {
            case 60: {
                if(this->positions[i] == 0) {
                   this->lines[i].insert(0, '_');
                } else {
                    this->positions[i]--;
                }
                break;
            }
            case 62: {
                if(++this->positions[i] == this->lines[i].length())
                   this->lines[i].push_back('_');
                break;
            }
            default: {
                break;
            }

        }
    }

    this->steps++;

    this->state = command->getNextState().toInt();
    if(this->state == 0)
        return false;

    return true;
}

void DemoMachine::setLength(int length) {
    this->length = length;
}

void DemoMachine::setPlot(Plot* plot) {
    this->plot = plot;
}

void DemoMachine::setProgressBar(QProgressBar *progress) {
   this->progress = progress;
}


QVector<QString> DemoMachine::combinations(int size) {
    QVector<QString> words;
    int wordCount = qPow(3, size);
    QString word(size, 'a');

    words.push_back(word);
    for(int i = 0; i < wordCount; i++) {
        for(int j = size - 1; j >= 0; j--) {
            if(word[j] == 'a') {
                word[j] = 'b';
                words.push_back(word);
                break;
            } else if (word[j] == 'b') {
                word[j] = 'c';
                words.push_back(word);
                break;
            } else if (word[j] == 'c') {
                word[j] = 'a';
            }

        }

    }
    return words;
}
