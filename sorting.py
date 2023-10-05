from time import perf_counter
import os
'testar 3 olika sorterings algoritmer, Felix Andersson, fean21@student.bth.se, DV1625'
def heapsort(lst, heap_depth=2):
    'heapsort funktion som sorterar en mängd med hjälp av heapifya mängden'
    heapsort_helpfunktion(lst, heap_depth)

def heapify(lst, lstleng, i, heap_depth):
    'sätter upp mängden i en ordning som kan visualiseras som ett binärt träd'
    largest = i
    for node in range(1 ,heap_depth + 1) :
        children = heap_depth * i + node
        if  children < lstleng and lst[largest] < lst[children]:
            largest = children
    if largest != i:
        lst[i], lst[largest] = lst[largest], lst[i]
        heapify(lst, lstleng, largest, heap_depth)

def heapsort_helpfunktion(lst, heap_depth):
    'kör heapsort'
    length = len(lst)
    if heap_depth>length:
        heap_depth = length
    if length>0:
        for i in range(length // heap_depth - 1, -1, -1):
            heapify(lst, length, i, heap_depth)
        for i in range(length-1, 0, -1):
            lst[i], lst[0] = lst[0], lst[i]
            heapify(lst, i, 0, heap_depth)

def quicksort_pivot_first(lst):
    'utför en quicksort med pivot värde på första index i mängden'
    quick_sort_helpfunktion(lst, 0, len(lst) - 1)

def quick_sort_helpfunktion(lst, low, high,):
    'kör quicksort'
    if low < high:
        seperate = partition(lst, low, high)
        quick_sort_helpfunktion(lst, low, seperate-1)
        quick_sort_helpfunktion(lst, seperate+1, high,)

def partition(lst, low, high,):
    'sorterar mängden'
    pivot = lst[low]
    i = low + 1
    for j in range(low,high+1):
        if lst[j] < pivot:
            lst[i], lst[j] = lst[j], lst[i]
            i += 1
    lst[low], lst[i-1] = lst[i-1], lst[low]
    return i-1

def quicksort_pivot_median(lst):
    'räknar ut medianen av tre element i mängden och sätter medelvärdet som pivot på första index'
    quick_sort_medain_helpfunktion(lst, 0, len(lst))

def partition_median(lst, low, high):
    'sorterar mängden'
    pivot_position= median(lst,low,high)
    pivot = lst[pivot_position]
    lst[low], lst[pivot_position] = lst[pivot_position], lst[low]
    i = low + 1
    for j in range(low+1, high, 1):
        if lst[j] < pivot:
            lst[i], lst[j] = lst[j], lst[i]
            i += 1
    lst[low], lst[i-1] = lst[i-1], lst[low]
    return i - 1

def median(lst, low, high):
    'Räknar ut medianen av första, melersta och sista elemt'
    middle = (low+high-1)//2
    first = lst[low]
    miditem = lst[middle]
    last = lst[high-1]
    if first <= miditem <= last:
        return middle
    if last <= miditem <= first:
        return middle
    if first <= last <= miditem:
        return high-1
    if miditem <= last <= first:
        return high-1
    return low

def quick_sort_medain_helpfunktion(lst, low, high,):
    'kör quicksort median funktionen'
    if low < high:
        seperate = partition_median(lst, low, high)
        quick_sort_medain_helpfunktion(lst, low, seperate)
        quick_sort_medain_helpfunktion(lst, seperate+1, high,)
    return lst


def main():
    i=0
    while(i<5):
        file = "sorted_reverse_100000.txt"
        list1 = open(f"Testdata/{file}").readlines()

        start = perf_counter()
        heapsort(list1,8)
        end = perf_counter()
        print("\nHeapsort:", end-start, "s i fil ", file, "\n")
        i+=1

if __name__ == '__main__':
    main()