# Bubble Sort
def bubble_sort(array):
    size = len(array)

    for i in range(size):
        is_sorted = True

        for j in range(size - i - 1):
            if array[j] > array[j + 1]:
                array[j], array[j + 1] = array[j + 1], array[j]
                is_sorted = False

        if is_sorted:
            break
    return array


# Recursive Insertion Sort
def insert_rec(elem, arr):
    if arr == []:
        return [elem]
    head = arr[0]
    if elem < head:
        return [elem] + arr
    tail = arr[1:]
    return [head] + insert_rec(elem, tail)


def isort_rec(arr):
    if arr == []:
        return []
    return insert_rec(arr[0], isort_rec(arr[1:]))


# Regular Insertion Sort
def insertion_sort(array):
    for i in range(1, len(array)):
        key_item = array[i]
        j = i - 1

        while j >= 0 and array[j] > key_item:
            array[j + 1] = array[j]
            j -= 1

        array[j + 1] = key_item
    return array


# Quick Sort With First Element Pivot
def quicksort(array):
    if len(array) < 2:
        return array

    low, same, high = [], [], []
    pivot = array[0]

    for item in array:
        if item < pivot:
            low.append(item)
        elif item == pivot:
            same.append(item)
        elif item > pivot:
            high.append(item)

    return quicksort(low) + same + quicksort(high)


def merge(left, right):
    if len(left) == 0:
        return right
    if len(right) == 0:
        return left

    result = []
    index_left = index_right = 0

    while len(result) < len(left) + len(right):

        if left[index_left] <= right[index_right]:
            result.append(left[index_left])
            index_left += 1
        else:
            result.append(right[index_right])
            index_right += 1

        if index_right == len(right):
            result += left[index_left:]
            break

        if index_left == len(left):
            result += right[index_right:]
            break

    return result


def merge_sort(array):
    if len(array) < 2:
        return array

    midpoint = len(array) // 2
    left_half = array[:midpoint]
    right_half = array[midpoint:]

    return merge(
        merge_sort(left_half),
        merge_sort(right_half)
    )
