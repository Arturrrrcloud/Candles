#include <iostream>
#include <fstream>

using namespace std;

const int MAX_SIZE = 20000;

struct Data {
    char date[11];
    double open;
    double high;
    double low;
    double close;
    int volume;
    char comma;
};

void readData(Data dataArray[], int max_size, const char filename[30], int& startIndex) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename << endl;
        return;
    }

    int dataCount = 0;

    int totalLines = 0;
    char line[256];
    while (file.getline(line, sizeof(line))) {
        totalLines++;
    }

    startIndex = max(0, totalLines - 200);

    file.clear();
    file.seekg(0, ios::beg);

    for (int i = 0; i < startIndex; i++) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    while (file.getline(dataArray[dataCount].date, 11, ',') &&
        file >> dataArray[dataCount].open >> dataArray[dataCount].comma >> dataArray[dataCount].high >> dataArray[dataCount].comma >>
        dataArray[dataCount].low >> dataArray[dataCount].comma >> dataArray[dataCount].close >> dataArray[dataCount].comma >>
        dataArray[dataCount].volume) {
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        dataCount++;
    }

    file.close();
}

void CreatingWykres(Data dataArray[], char** wykres, int row) {
    double x = 0;
    if (row >= 0 && row < 60) {
        x = 0.3;
    }
    else if (row >= 60 && row <= 100) {
        x = 0.15;
    }
    else {
        cout << "Too much";
        return;
    }
    for (int i = 0; i < 200; i++) {
        int j = int(dataArray[i].close);
        if (dataArray[i].open <= dataArray[i].close) {
            while (dataArray[i].open <= dataArray[i].close) {
                wykres[j][i] = 'O';
                dataArray[i].close = dataArray[i].close - x;
                j--;
            }
        }
        else if (dataArray[i].open >= dataArray[i].close) {
            while (dataArray[i].open >= dataArray[i].close) {
                wykres[j][i] = '#';
                dataArray[i].close = dataArray[i].close + x;
                j++;
            }
        }
        int k = int(dataArray[i].high);
        if (dataArray[i].high >= dataArray[i].low) {
            while (dataArray[i].high >= dataArray[i].low) {
                if (wykres[k][i] == ' ') {
                    wykres[k][i] = '|';
                }
                dataArray[i].high = dataArray[i].high - x;
                k--;
            }
        }
        else if (dataArray[i].high <= dataArray[i].low) {
            while (dataArray[i].high <= dataArray[i].low) {
                if (wykres[k][i] == ' ') {
                    wykres[k][i] = '|';
                }
                dataArray[i].high = dataArray[i].high + x;
                k++;
            }
        }
        if (i == 199) {
            for (int j = 0; j < row / 2; j++) {
                for (int k = 0; k < 200; k++) {
                    char temp = wykres[j][k];
                    wykres[j][k] = wykres[(row - 1) - j][k];
                    wykres[(row - 1) - j][k] = temp;
                }
            }
        }
    }
}

void DataAdditionweek(Data dataArray[], char** wykres, int row) {
    double x = 0;
    if (row >= 0 && row < 60) {
        x = 0.5;
    }
    else if (row >= 60 && row <= 100) {
        x = 0.25;
    }
    else {
        cout << "Too much";
        return;
    }
    for (int i = 0; i < 196; i += 7) {
        int j = int(dataArray[i].close);
        double maxHigh = dataArray[i].high;
        double minLow = dataArray[i].low;
        if (dataArray[i].open <= dataArray[i + 6].close) {
            while (dataArray[i].open <= dataArray[i + 6].close) {
                wykres[j][i] = 'O';
                dataArray[i + 6].close = dataArray[i + 6].close - x;
                j--;
            }
        }
        else if (dataArray[i].open >= dataArray[i + 6].close) {
            while (dataArray[i].open >= dataArray[i + 6].close) {
                wykres[j][i] = '#';
                dataArray[i + 6].close = dataArray[i + 6].close + x;
                j++;
            }
        }
        for (int k = i; k <= i + 6; k++) {
            if (dataArray[k].high > maxHigh) {
                maxHigh = dataArray[k].high;
            }
            if (dataArray[k].low < minLow) {
                minLow = dataArray[k].low;
            }
        }
        j = int(maxHigh);
        if (maxHigh >= minLow) {
            while (maxHigh >= minLow) {
                if (wykres[j][i] == ' ') {
                    wykres[j][i] = '|';
                }
                maxHigh = maxHigh - x;
                j--;
            }
        }
        else if (maxHigh <= minLow) {
            while (maxHigh <= minLow) {
                if (wykres[j][i] == ' ') {
                    wykres[j][i] = '|';
                }
                maxHigh = maxHigh + x;
                j++;
            }
        }
        if (i == 189) {
            for (int j = 0; j < row / 2; j++) {
                for (int k = 0; k < 200; k++) {
                    char temp = wykres[j][k];
                    wykres[j][k] = wykres[(row - 1) - j][k];
                    wykres[(row - 1) - j][k] = temp;
                }
            }
        }
    }
}

void DataAdditionmonth(Data dataArray[], char** wykres, int row) {
    double x = 0;
    if (row >= 0 && row < 60) {
        x = 0.5;
    }
    else if (row >= 60 && row <= 100) {
        x = 0.35;
    }
    else {
        cout << "Too much";
        return;
    }
    for (int i = 0; i < 180; i += 30) {
        int j = int(dataArray[i].close);
        double maxHigh = dataArray[i].high;
        double minLow = dataArray[i].low;
        if (dataArray[i].open <= dataArray[i + 29].close) {
            while (dataArray[i].open <= dataArray[i + 29].close) {
                wykres[j][i] = 'O';
                dataArray[i + 29].close = dataArray[i + 29].close - x;
                j--;
            }
        }
        else if (dataArray[i].open >= dataArray[i + 29].close) {
            while (dataArray[i].open >= dataArray[i + 29].close) {
                wykres[j][i] = '#';
                dataArray[i + 29].close = dataArray[i + 29].close + x;
                j++;
            }
        }
        for (int k = i; k <= i + 29; k++) {
            if (dataArray[k].high > maxHigh) {
                maxHigh = dataArray[k].high;
            }
            if (dataArray[k].low < minLow) {
                minLow = dataArray[k].low;
            }
        }
        j = int(maxHigh);
        if (maxHigh >= minLow) {
            while (maxHigh >= minLow) {
                if (wykres[j][i] == ' ') {
                    wykres[j][i] = '|';
                }
                maxHigh = maxHigh - x;
                j--;
            }
        }
        else if (maxHigh <= minLow) {
            while (maxHigh <= minLow) {
                if (wykres[j][i] == ' ') {
                    wykres[j][i] = '|';
                }
                maxHigh = maxHigh + x;
                j++;
            }
        }
        if (i == 150) {
            for (int j = 0; j < row / 2; j++) {
                for (int k = 0; k < 200; k++) {
                    char temp = wykres[j][k];
                    wykres[j][k] = wykres[(row - 1) - j][k];
                    wykres[(row - 1) - j][k] = temp;
                }
            }
        }
    }
}

void DeleteWykres(char** wykres, int rows, int cols, const char filename1[30]) {
    ofstream file(filename1);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename1 << endl;
        return;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            wykres[i][j] = ' ';
            file << wykres[i][j];
        }
        file << endl;
    }
    file.close();
}

void WriteData(char** wykres, int rows, int cols, const char filename1[30]) {
    ofstream file(filename1);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename1 << endl;
        return;
    }
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            file << wykres[i][j];
        }
        file << endl;
    }
    file.close();
}

void WritePartData(Data dataArray[], char** wykres, int row, const char filename1[30], char part1[11], char part2[11]) {
    int i = 0;
    while (strcmp(dataArray[i].date, part1) != 0) {
        i++;
    }
    int j = i;
    while (strcmp(dataArray[j].date, part2) != 0) {
        j++;
    }
    ofstream file(filename1);
    if (!file.is_open()) {
        cerr << "Unable to open file: " << filename1 << endl;
        return;
    }
    for (int x = 0; x < row; x++) {
        for (int y = i; y < j; y++) {
            file << wykres[x][y];
        }
        file << endl;
    }
    file.close();
    for (int x = 0; x < row; x++) {
        for (int y = i; y < j; y++) {
            cout << wykres[x][y];
        }
        cout << endl;
    }
}

void freeMemory(char** wykres, int rows) {
    for (int i = 0; i < rows; i++) {
        delete[] wykres[i];
    }
    delete[] wykres;
}

int main() {
    char part1[30];
    char part2[30];
    char filename[30];
    char filename1[30];
    cout << "Artur Nuso 201272" << endl;

    while (true) {
        cout << "Choose file to read: ";
        cin >> filename;
        int row;
        cout << "Choose height: ";
        cin >> row;

        char** wykres = new char* [row];
        for (int i = 0; i < row; i++) {
            wykres[i] = new char[200];
            for (int j = 0; j < 200; j++) {
                wykres[i][j] = ' ';
            }
        }

        Data dataArray[250];
        int startIndex = 0;
        char move;
        DeleteWykres(wykres, row, 200, filename1);
        cout << "Move(q - end, g - generate wykres, p - generate part of wykres): ";
        cin >> move;
        if (move == 'q') {
            cout << "End Program" << endl;
            break;
        }
        else if (move == 'g') {
            cout << "Choose time(d - day, w - week, m - month): ";
            cin >> move;
            cout << "Choose file to write: ";
            cin >> filename1;
            if (move == 'd') {
                readData(dataArray, MAX_SIZE, filename, startIndex);
                CreatingWykres(dataArray, wykres, row);
                WriteData(wykres, row, 200, filename1);
            }
            else if (move == 'w') {
                readData(dataArray, MAX_SIZE, filename, startIndex);
                DataAdditionweek(dataArray, wykres, row);
                WriteData(wykres, row, 200, filename1);
            }
            else if (move == 'm') {
                readData(dataArray, MAX_SIZE, filename, startIndex);
                DataAdditionmonth(dataArray, wykres, row);
                WriteData(wykres, row, 200, filename1);
            }
        }
        else if (move == 'p') {
            cout << "Choose date start(YYYY-MM-DD): ";
            cin >> part1;
            cout << "Choose date end(YYYY-MM-DD): ";
            cin >> part2;
            cout << "Choose time(d - day, w - week, m - month): ";
            cin >> move;
            cout << "Choose file to write: ";
            cin >> filename1;
            if (move == 'd') {
                readData(dataArray, MAX_SIZE, filename, startIndex);
                CreatingWykres(dataArray, wykres, row);
                WritePartData(dataArray, wykres, row, filename1, part1, part2);
            }
            else if (move == 'w') {
                readData(dataArray, MAX_SIZE, filename, startIndex);
                DataAdditionweek(dataArray, wykres, row);
                WritePartData(dataArray, wykres, row, filename1, part1, part2);
            }
            else if (move == 'm') {
                readData(dataArray, MAX_SIZE, filename, startIndex);
                DataAdditionmonth(dataArray, wykres, row);
                WritePartData(dataArray, wykres, row, filename1, part1, part2);
            }
        }
        freeMemory(wykres, row);
    }
    return 0;
}

