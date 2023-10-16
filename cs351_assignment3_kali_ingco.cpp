#include <iostream>
#include <fstream>
#include <mutex>
#include <thread>
#include <string>


using namespace std;

std::mutex mtx;

void writeLetters(); //function declaration
void writeNums(); //function declaration 

int main(){
  
    //create and open a text file
    ofstream file("synch.txt");

    thread th1(writeNums); //thread that writes numbers to file
    thread th2(writeLetters); //thread that writes letters to file 

    th1.join();
    th2.join();

    file.close();
    return 0;
}


void writeLetters() {
    mtx.lock(); //mutex lock
    ofstream file("synch.txt", std::ios_base::app); //will append to file
    for(int i = 0; i<20; i++){
        for(char letter = 'A'; letter <= 'Z'; letter++){
    file << letter << " "; //will print A-Z
        }
        file << "\n"; //newline for next instance of A-Z
    }
    mtx.unlock(); //mutex unlock 
    
}


void writeNums() {
    mtx.lock(); //mutex lock
    ofstream file("synch.txt", std::ios_base::app); //will append to file 
    for(int i=0; i<20; i++){
        for(int num = 1; num <= 26; num++){
        file << num << " "; //will print 1-26
        }
        file << "\n"; //newline for new instance of 1-26
    }
    mtx.unlock(); //mutex unlock
}