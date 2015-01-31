### NAME

    `insertion_sort` - insertion sort


### SYNOPSIS

    #include <stdio.h>

    insertion_sort(
        void *arr,
        size_t el_sz,
        int start,
        int end,
        int(*cmp)(const void *, const void *)
    )


### DESCRIPTION

- Class: Sorting
- Data Structure: Array
- Worst case: $O(n^2)$ comparisons, swaps
- Best case: $O(n^2)$ comparisons, $O(1)$ swaps
- Average case: $O(n^2)$ comparisons, swaps
- Worst case space complexity: $O(n)$ total, $O(1)$ auxiliary

Insertion sort is a simple sorting algorithm that builds the final sorted array
(or list) one time at a time. It is much less efficient on large lists than
more advanced algorithms such as quick sort, heap sort , or merge sort.
However, Insertion sort provides several advantages:

- Simple implementation
- Efficient for (quite) small data sets
- Adaptive (i.e. efficient) for datasets that are already substantially sorted:
  the time complexity is $O(n + d)$, where $d$ is the number of inversions.
- More efficient in practice than most other simple quadratic (i.e. $O(n^2)$)
  algorithms such as selection sort or bubble sort; the best case (nearly
  sorted input) is $O(n)$.
- Stable; i.e. does not change the relative order of elements with equal keys
- In-place; i.e. only requires a constant amount $O(1)$ of additional memory
  space
- Online: i.e. can sort a list as it receives it

When humans manually sort something (for example, a deck of playing cards),
most use a method that is similar to INSERT SORT.


### ARGUMENTS


### PSEUDO CODE

    INSERT(A, pos, value)

        i = pos - 1

        while (i >= 0 and A[i] > value)
            A[i + 1] = A[i]
            i = i - 1

        A[i + 1] = value

    INSERTION-SORT(A)

        for (i = 1 to n - 1)
            INSERT(A, i, A[i])


Insertion sort iterates, consuming one input element each repetition, and
growing a sorted output list. On a repetition, insertion sort removes one
element from the input data, finds the location it belongs within the sorted
list, and inserts it there. It repeasts until no input elements remain.

Sorting is typically does in-place, by interating up the array, growing the
sorted list behind it. At each array-position, it check sthe value there
against the larges value in the sorted list (which happens to be next to it, in
the previous array-position checked). If larger, it leaves the elemnt in place
and moves to the next. If smaller, it finds the correct position within the
sorted list, shifts all the larger values up to make a space, and inserts into
that correct position.

The resulting array after $k$ iterations has the property where the first $k +
1$ entries are sorted ("$+ 1$" because the first entry is skipped). In each
iteration the first remaining entry of the input is removed, and inserted into
the result at the correct position, thys extending the result.
