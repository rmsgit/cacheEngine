//
// Created by Ruwan on 10/20/2017.
//

#include <iostream>
#include <thread>
/*
#ifndef CACHEENGINE_CACHESTORE_H
#define CACHEENGINE_CACHESTORE_H

#endif //CACHEENGINE_CACHESTORE_H*/
using namespace std;





namespace CacheStore {

    int nextAccessIndex = 0;

    int BLOCK_SIZE = 5;


    struct Block{
        int ref;
        int attempt;
        string value;
    };

    struct CacheRow {
    private:
        int nextAccessIndex;
    public:
        Block *cache;
        int ROW_SIZE;

        void init(int rowSize) {
            this->cache = new Block[rowSize];
            this->ROW_SIZE = rowSize;
            this->nextAccessIndex = 0;
            for (int i=0; i < rowSize; i++) {
                this->cache[i].ref = 0;
                this->cache[i].attempt = 0;
                this->cache[i].value = "";
            }
        };

        int addBlock (Block block) {
            int hasIndex = this->hasHadata(block.ref);
            switch (hasIndex){
                case -1:
                    this->cache[this->nextAccessIndex] = block;
                    this->nextAccessIndex++;
                    cout << "sleep" << endl;
                    Sleep(1000);

                    cout << "added" << endl;
                    break;
                default:
                    this->cache[hasIndex].attempt++;
                    this->cache[hasIndex].value = block.value;
                    break;
            }
            if(this->nextAccessIndex == this->ROW_SIZE) this->nextAccessIndex = 0;
            return this->nextAccessIndex - 1;

        }

        void removeBlock (int ref) {
            for(int i =0; i < this->ROW_SIZE; i++){

                 if(this->cache[i].ref == ref) {
                     for (int j = i; j < (this->ROW_SIZE-1); j++ ) {
                         Block temp  = cache[j];
                         cache[j] = cache[j+1];
                         cache[j+1] = temp;
                     }
                     Block empty;
                     empty.ref = 0;
                     empty.attempt = 0;
                     empty.value = "";
                     this->cache[this->ROW_SIZE-1] = empty;
                     this->nextAccessIndex = this->ROW_SIZE-2;
                     cout << "removed" << endl;
                 }
            }
        }
        int hasHadata(int ref){
            for(int i =0; i < this->ROW_SIZE; i++)
                if(this->cache[i].ref == ref) return i;
            return -1;
        }


        void viewAll(){
            for(int i =0; i < this->ROW_SIZE; i++) if(this->cache[i].ref) cout << this->cache[i].ref << "\t\t" << this->cache[i].attempt << "\t" << this->cache[i].value << endl;
        }

    };





}