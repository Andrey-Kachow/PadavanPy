
# linear search
def linear_search(search_item, items):
    for idx in range(len(items)):
        if items[idx] == search_item:
            return idx
    return -1

# binary search
def binary_search(search_item, items):
    low = 0
    high = len(items) - 1
    while low != high:
        mid = (low + high) // 2
        if items[mid] == search_item:
            return mid
        else:
            if items[mid] < search_item:
                low = mid + 1
            else:
                high = mid - 1
    return -1
