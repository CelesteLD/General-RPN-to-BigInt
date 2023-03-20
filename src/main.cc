/**
 * @file main.cc
 * @author Celeste Luis Díaz (alu0101321660@ull.edu.es)
 * @brief Main program that reads the input file and calls the functions to process the data
 * @version 0.1
 * @date 2023-03-12
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>

#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
#include <sstream>
#include <map>
#include <fstream>
#include <stack>

#include "../include/bigint.h"
#include "../include/number.h"

std::vector<std::string> readData(std::string filename);
void processData(std::map<std::string, Number*>& board, std::string& line);
std::vector<std::string> processLine(std::string& line);

bool existOnBoard(std::map<std::string, Number*>& board, std::string& label);
void printBoard(std::map<std::string, Number*>& board, std::ofstream &fileout);

int main(int argc, char const *argv[]) {

    std::vector<std::string> data = readData(argv[1]);
    std::map<std::string, Number*> board;

    for (auto& line : data) {
        processData(board, line);
    }

    std::ofstream fileout;
    fileout.open("output.txt");
    printBoard(board, fileout);
    fileout.close();

    return 0;
}


std::vector<std::string> readData(std::string filename) {
    std::ifstream file(filename);
    std::vector<std::string> data;
    std::string line;
    while (std::getline(file, line)) {
        data.push_back(line);
    }
    return data;
}

void processData(std::map<std::string, Number*>& board, std::string& line) {

    std::stack<std::string> stack;
    
    // Si en la linea hay un =, se llamará a la función processAssigment

    if (line.find('=') != std::string::npos) {

        // Introducir cada elemento de la línea en un vector de strings
        std::vector<std::string> assigment = processLine(line);
        // Eliminar del vector la posición 1 (el =)
        assigment.erase(assigment.begin() + 1);
        // Eliminar de la posición 1 el último caracter (la ,)
        assigment[1].erase(assigment[1].size() - 1);

        // for (auto& word : assigment) {
        //     std::cout << word << std::endl;
        // }

        std::string label = assigment[0]; // Key
        int base = std::stoi(assigment[1]); // Base
        std::string value = assigment[2]; // Value of number

        // std::cout << "label: " << label << std::endl;
        // std::cout << "base: " << base << std::endl;
        // std::cout << "value: " << value << std::endl;

        // Crear un nuevo número con la base y el valor
        Number* number = Number::create(base, value);

        // Introducir el número en el mapa
        board[label] = number;

        // std::cout << "board[label]: " << *board[label] << std::endl;

    } else if (line.find('?') != std::string::npos) {

        // Si en la línea hay un ?, se llamará a la función processOperation
        std::vector<std::string> operation = processLine(line);
        // Eliminar del vector la posición 1 (el ?)
        operation.erase(operation.begin() + 1);

        std::string label = operation[0]; // Key

        for (int i = 1; i < operation.size(); i++) {
            if (operation[i].size() != 1) {
                stack.push(operation[i]);
            } else {
                if (operation[i] == "+") {
                    if (stack.size() >= 2) {
                        std::string n2 = stack.top();
                        stack.pop();
                        std::string n1 = stack.top();
                        stack.pop();
                        if (existOnBoard(board, n2) && existOnBoard(board, n1)) {
                            Number* result = board[n1]->add(board[n2]);
                            stack.push(label);
                            board[label] = result;
                        } else {
                            std::cout << "Error: No existe el número en el tablero" << std::endl;
                        }
                    }
                } else if (operation[i] == "-") {
                    if (stack.size() >= 2) {
                        std::string n2 = stack.top();
                        stack.pop();
                        std::string n1 = stack.top();
                        stack.pop();
                        if (existOnBoard(board, n2) && existOnBoard(board, n1)) {
                            Number* result = board[n1]->subtract(board[n2]);
                            stack.push(label);
                            board[label] = result;
                        } else {
                            std::cout << "Error: No existe el número en el tablero" << std::endl;
                        }
                    }
                } else if (operation[i] == "*") {
                    if (stack.size() >= 2) {
                        std::string n2 = stack.top();
                        stack.pop();
                        std::string n1 = stack.top();
                        stack.pop();
                        if (existOnBoard(board, n2) && existOnBoard(board, n1)) {
                            Number* result = board[n1]->multiply(board[n2]);
                            stack.push(label);
                            board[label] = result;
                        } else {
                            std::cout << "Error: No existe el número en el tablero" << std::endl;
                        }
                    }
                } else if (operation[i] == "/") {
                    if (stack.size() >= 2) {
                        std::string n2 = stack.top();
                        stack.pop();
                        std::string n1 = stack.top();
                        stack.pop();
                        if (existOnBoard(board, n2) && existOnBoard(board, n1)) {
                            Number* result = board[n1]->divide(board[n2]);
                            stack.push(label);
                            board[label] = result;
                        } else {
                            std::cout << "Error: No existe el número en el tablero" << std::endl;
                        }
                    }
                } else if (operation[i] == "%") {
                    if (stack.size() >= 2) {
                        std::string n2 = stack.top();
                        stack.pop();
                        std::string n1 = stack.top();
                        stack.pop();
                        if (existOnBoard(board, n2) && existOnBoard(board, n1)) {
                            Number* result = board[n1]->module(board[n2]);
                            stack.push(label);
                            board[label] = result;
                        } else {
                            std::cout << "Error: No existe el número en el tablero" << std::endl;
                        }
                    }
                }
            }
        }
    } else {
        std::cout << "Error: Línea no válida" << std::endl;
    }
}

std::vector<std::string> processLine(std::string& line) {
    std::vector<std::string> assigment;
    std::string word;
    std::stringstream ss(line);
    while (ss >> word) {
        assigment.push_back(word);
    }
    return assigment;
}

bool existOnBoard(std::map<std::string, Number*>& board, std::string& label) {
    return board.find(label) != board.end();
}

void printBoard(std::map<std::string, Number*>& board, std::ofstream &fileout) {
    // Imprimir la etiqueta, un =, la base del número y el valor del número
    for (auto& pair : board) {
        fileout << pair.first << " = " << pair.second->getBase() << ", " << *pair.second << std::endl;
    }
}

