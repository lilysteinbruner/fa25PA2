//
// Created by Manju Muralidharan on 10/19/25.
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        if (size >= 64) {
            cout << "Heap is full, cannot push index " << idx << "\n";
        }
        data[size] = idx;             // insert new element at the end
        upheap(size, weightArr);      // restore order using upheap()
        ++size;
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Replace root with last element, then call downheap()
        if (size == 0) {
            cout << "Heap is empty, nothing to remove.\n";
            return 0;
        }

        // remove and return smallest index
        int smallestIdx = data[0];
        if (size == 1) {
            --size;
            return smallestIdx;
        }

        //move last element to root, decrease size, and downheap
        data[0] = data[size - 1];
        --size;
        downheap(0, weightArr);
        return smallestIdx;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (pos > 0) {
            int parent = (pos - 1) / 2;
            if (weightArr[data[pos]] < weightArr[data[parent]]) {
                int temp = data[pos];
                data[pos] = data[parent];
                data[parent] = temp;
                pos = parent;
            } else {
                return;
            }
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        while (true) {
            int left = 2 * pos + 1;
            int right = left + 1;
            if (left >= size) return;  // no children

            // pick smaller child
            int smallest = left;
            int leftIdx = data[left];
            int smallestIdx = data[smallest];
            int leftW = weightArr[leftIdx];
            int smallestW = weightArr[smallestIdx];

            if (right < size) {
                int rightIdx = data[right];
                int rightW = weightArr[rightIdx];
                // if right is smaller or tie and smaller index, choose right
                if (rightW < leftW || (rightW == leftW && rightIdx < leftIdx)) {
                    smallest = right;
                    smallestIdx = data[smallest];
                    smallestW = weightArr[smallestIdx];
                }
            }

            int parentIdx = data[pos];
            int parentW = weightArr[parentIdx];

            // if parent is <= smallest child (by weight, tie-break by smaller index), stop
            if (parentW < smallestW || (parentW == smallestW && parentIdx < smallestIdx)) {
                return;
            }

            // else, swap parent with the smallest child and continue
            int temp = data[pos];
            data[pos] = data[smallest];
            data[smallest] = temp;
            pos = smallest;
        }
    }
};

#endif