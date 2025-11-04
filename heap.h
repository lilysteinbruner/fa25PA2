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
            return;
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
            return -1;
        }

        // remove and return smallest index
        int smallestIdx = data[0];

        //move last element to root, decrease size, and downheap
        if (size > 0) {
            data[0] = data[size - 1];
        }

        --size;
        downheap(0, weightArr);


        return smallestIdx;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        while (pos > 0) {
            int parent = (pos - 1) / 2;
            int childIdx = data[pos];
            int parentIdx = data[parent];

            int childW = weightArr[childIdx];
            int parentW = weightArr[parentIdx];

            //if child has smaller or equal weight but smaller index, swap upward.
            if (childW < parentW || (childW == parentW && childIdx < parentIdx)) {
                int tmp = data[pos];
                data[pos] = data[parent];
                data[parent] = tmp;
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
            int smallestIdx = leftIdx;
            int smallestW = weightArr[leftIdx];

            if (right < size) {
                int rightIdx = data[right];
                int rightW = weightArr[rightIdx];
                // if right is smaller or tie and smaller index, choose right
                if (rightW < smallestW || (rightW == smallestW && rightIdx < smallestIdx)) {
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