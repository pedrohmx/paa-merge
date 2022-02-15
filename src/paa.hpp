#ifndef PAA_HPP_INCLUDED
#define PAA_HPP_INCLUDED

namespace paa{

void merge(int *arr, int start, int half, int end) {
    int s1 = start, s2 = half+1;
    int sa = 0, size = end - start + 1;
    auto aux = new int[size];

    // check both
    while (s1 <= half && s2 <= end) {
        if (arr[s1] < arr[s2]) {
            aux[sa] = arr[s1];
            s1++;
        } else {
            aux[sa] = arr[s2];
            s2++;
        }
        sa++;
    }
    // check arr1
    while (s1 <= half) {
        aux[sa] = arr[s1];
        s1++;
        sa++;
    }
    // check arr2
    while (s2 <= end) {
        aux[sa] = arr[s2];
        s2++;
        sa++;
    }
    // move
    for (sa = start; sa <= end; sa++) {
        arr[sa] = aux[sa-start];
    }

    delete[] aux;
}

void merge_sort(int *arr, int start, int end) {
    if (start < end) {
        int half = (end + start)/2;
        merge_sort(arr, start, half);
        merge_sort(arr, half+1, end);
        merge(arr, start, half, end);
    }
}

void super_merge_sort(int *arr, int start, int end) {
    if (start < end) {
        int half = (end + start)/2;
        int h1 = (half + start)/2;
        int h2 = (end + half)/2;

        super_merge_sort(arr, start, h1);
        super_merge_sort(arr, h1+1, half);
        super_merge_sort(arr, half+1, h2);
        super_merge_sort(arr, h2+1, end);

        merge(arr, start, h1, half);
        merge(arr, half+1, h2, end);
        merge(arr, start, half, end);
    }
}

};

#endif