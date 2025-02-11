# Bug Documentation for `practice03.cpp`

## Bug 1: **Off-by-one Error in `sumRange` Method**
- **Issue**: The `sumRange` method uses a loop with the condition `i < end`, which causes it to exclude the `end` value in the sum.
- **Cause**: The loop condition should have included the `end` value to ensure the correct sum. 
- **Fix**: The loop condition was updated from `for (int i = start; i < end; i++)` to `for (int i = start; i <= end; i++)` to include the `end` value in the summation.
- **Expected Behavior**: Now the method sums all integers from `start` to `end`, inclusive.

### Bug 2: **Out-of-Bounds Access in `containsNegative` Method**
- **Issue**: The `containsNegative` method has a loop with the condition `i <= numbers.size()`, which leads to accessing an out-of-bounds index when `i == numbers.size()`.
- **Cause**: The loop condition should stop at `i < numbers.size()`, ensuring that the indices are within bounds.
- **Fix**: The loop was modified from `for (size_t i = 0; i <= numbers.size(); i++)` to `for (size_t i = 0; i < numbers.size(); i++)` to prevent out-of-bounds access. Additionally, the condition checking for negative values was changed from `if (numbers[i] > 0)` to `if (numbers[i] < 0)` to correctly detect negative numbers.
- **Expected Behavior**: Now the method correctly checks for negative numbers in the list and handles the edge case where the list is empty.

### Bug 3: **Off-by-one Error in `findMax` Method**
- **Issue**: The `findMax` method uses a loop with the condition `i <= numbers.size()`, which leads to out-of-bounds access when `i == numbers.size()`.
- **Cause**: The loop should iterate up to `i < numbers.size()` to avoid accessing an invalid index.
- **Fix**: The loop was updated from `for (size_t i = 1; i <= numbers.size(); i++)` to `for (size_t i = 1; i < numbers.size(); i++)` to ensure that it only accesses valid indices. 
- **Expected Behavior**: The method now correctly finds the maximum value in the list, including when the list has only one element, and it no longer attempts to access out-of-bounds memory.

---

## Summary of Changes
- Fixed off-by-one error in `sumRange` by modifying the loop condition to include `end`.
- Prevented out-of-bounds access in `containsNegative` by adjusting the loop condition and correcting the logic to detect negative numbers.
- Corrected the loop condition in `findMax` to avoid out-of-bounds access and ensure the correct maximum value is returned.

After applying these fixes, all methods work as expected, and the unit tests now pass successfully.

