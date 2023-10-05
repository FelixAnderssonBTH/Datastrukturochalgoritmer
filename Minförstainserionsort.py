
# def partition(arr, low, high,):
#     pivot = arr[low]
#     i = low + 1
#     for j in range(low,high+1):
#         if arr[j] < pivot:
#             arr[i], arr[j] = arr[j], arr[i]
#             i += 1
#     arr[low], arr[i-1] = arr[i-1], arr[low]
#     return i-1

# def quick_sort(arr, low, high,):
#     if low < high:
#         seperate = partition(arr, low, high)
#         quick_sort(arr, low, seperate-1)
#         quick_sort(arr, seperate+1, high,)
#     return arr

# array = [5,1,3,9,8,2,7,342,432,234,2,52,3,356,85,67,4,1,4,77,54,3]

# quick_sort(array, 0, len(array) - 1)
# print(array)





# def partition(arr, low, high):
#     pivot = arr[low]
#     i = low + 1
#     for j in range(low,high+1):
#         if arr[j] < pivot:
#             arr[i], arr[j] = arr[j], arr[i]
#             i += 1
#     arr[low], arr[i-1] = arr[i-1], arr[low]
#     return i-1

# def median(arr):
#     low = arr[0]
#     high = len(arr)-1
#     middle = arr[int(high/2)]
#     if low>high and low >middle:
#         if high>middle:
#             return len(arr)-1
#         else:
#             return int(high/2)
#     return 0

# def quick_sort_median(arr, low, high,):
#     pivot = median(arr)
#     arr[0],arr[pivot]=arr[pivot],arr[0]
#     if low < high:
#         seperate = partition(arr, low, high)
#         quick_sort_median(arr, low, seperate-1)
#         quick_sort_median(arr, seperate+1, high,)
#     return arr
# array = [5,1,3,9,8,2,4,1,5432,23,456,543,4,567,6,543,2,345,67,65,432,345,678,90,0,9,9,98,7,65,43,2,11,1,11,2,345,3,4,4,4,5,4,6,4,6,4,6,5,7,8,8,8,6,6,7,6,5,5,6,]

# quick_sort_median(array, 0, len(array) - 1)
# print(array)

# def quicksort_pivot_median(lst):
#     """Quicksort funktion med pivot på median position"""
#     quicksort_median_pivot_helper(lst, 0, len(lst))

# def quicksort_median_pivot_helper(lst, low, high):
#     """Utför quicksorten med pivot på första"""
#     if low < high:
#         pivot = partition_median(lst, low, high)
#         quicksort_median_pivot_helper(lst, low, pivot)
#         quicksort_median_pivot_helper(lst, pivot + 1, high)

# def median_of_three(lst, low, high):
#     """plockar ut medianen av tre tal"""
#     middle = (low+high-1)//2

#     i = lst[low]

#     j = lst[middle]

#     k = lst[high-1]

#     if i <= j <= k:
#         return j, middle
#     if k <= j <= i:
#         return j, middle
#     if i <= k <= j:
#         return k, high-1
#     if j <= k <= i:
#         return k, high-1
#     return i, low

# def partition_median(lst, low, high):
#     """partition med pivot på första elementet"""
#     pivot, pivot_position = median_of_three(lst, low, high)
#     lst[low], lst[pivot_position] = lst[pivot_position], lst[low]
#     i = low + 1
#     for j in range(low+1, high, 1):
#         if lst[j] < pivot:
#             lst[i], lst[j] = lst[j], lst[i]
#             i += 1
#     lst[low], lst[i-1] = lst[i-1], lst[low]
#     return i - 1

# def heapsort(lst, heap_depth=2):
#     'heapsort funktion som sorterar en mängd med hjälp av heapifya mängden'
#     heapSort_helpfunktion(lst, heap_depth)

# def heapify(lst, lstleng, i, heap_depth):
#     'sätter upp mängden i en ordning som kan visualiseras som ett binärt träd'
#     largest = i
#     for node in range(1 ,heap_depth + 1) :
#         children = heap_depth * i + node
#         if  children < lstleng and lst[largest] < lst[children]:
#             largest = children
#     if largest != i:
#         lst[i], lst[largest] = lst[largest], lst[i]
#         heapify(lst, lstleng, largest, heap_depth)

# def heapSort_helpfunktion(lst, heap_depth):
#     'kör heapsort'
#     length = len(lst)
#     for i in range(length // heap_depth - 1, -1, -1):
#         heapify(lst, length, i, heap_depth)
#     for i in range(length-1, 0, -1):
#         lst[i], lst[0] = lst[0], lst[i]
#         heapify(lst, i, 0, heap_depth)
def quicksort_pivot_median(lst):
    'räknar ut medianen av tre element i mängden och sätter medelvärdet som pivot på första index'
    quick_sort_medain_helpfunktion(lst, 0, len(lst))

def partition_median(lst, low, high):
    'sorterar mängden'
    pivot_position= median(lst,low,high)
    #print(pivot_position)
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

arr = [34,56,21,42,99,66,43,28,11,67,30]
quicksort_pivot_median(arr)
n = len(arr)
print (arr)

