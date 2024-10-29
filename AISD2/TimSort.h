#ifndef TIMSORT_H
#define TIMSORT_H

#include <vector>
#include <stack>
#include <utility>
#include <algorithm>

template <typename T>
class TimSort {
private:
    size_t getMinrun(size_t n);
    void insertionSort(std::vector<T>& arr, size_t left, size_t right);
    size_t gallopSearch(const std::vector<T>& arr, T key, size_t start, size_t end, bool rightMost);
    void merge(std::vector<T>& arr, size_t leftStart, size_t mid, size_t rightEnd);

public:
    bool isSorted(const std::vector<T>& arr, long long int start, long long int end);
    void sort(std::vector<T>& arr);
};

template <typename T>
size_t TimSort<T>::getMinrun(size_t n) 
{
    size_t r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

template <typename T>
void TimSort<T>::insertionSort(std::vector<T>& arr, size_t left, size_t right) 
{
    for (size_t i = left + 1; i <= right; ++i) {
        T key = arr[i];
        size_t j = i;

        while (j > left && arr[j - 1] > key) {
            arr[j] = arr[j - 1];
            --j;
        }
        arr[j] = key;
    }
}

template <typename T>
bool TimSort<T>::isSorted(const std::vector<T>& arr, long long int start, long long int end) 
{
    for (size_t i = start+1; i < end; ++i) {
        if (arr[i - 1] > arr[i]) {
            return false;
        }
    }
    return true;
}

template <typename T>
size_t TimSort<T>::gallopSearch(const std::vector<T>& arr, T key, size_t start, size_t end, bool rightMost) 
{
    size_t result = SIZE_MAX;
    if (rightMost) {
        while (start <= end && end != SIZE_MAX) {
            size_t mid = start + ((end - start) / 2);

            if (arr[mid] <= key) {
                result = mid;
                start = mid + 1;
            }
            else {
                end = mid - 1;
            }
        }
    }
    else {
        while (start <= end && end != SIZE_MAX) {
            size_t mid = start + ((end - start) / 2);

            if (arr[mid] >= key) {
                result = mid;
                end = mid - 1;
            }
            else {
                start = mid + 1;
            }
        }
    }

    return result;
}

template<typename T>
void TimSort<T>::merge(std::vector<T>& arr, size_t leftStart, size_t mid, size_t rightEnd) 
{
    size_t leftSize = mid - leftStart + 1;
    size_t rightSize = rightEnd - mid;

    bool leftIsSmaller = (leftSize <= rightSize);
    std::vector<T> tempArr = leftIsSmaller
        ? std::vector<T>(arr.begin() + leftStart, arr.begin() + mid + 1)
        : std::vector<T>(arr.begin() + mid + 1, arr.begin() + rightEnd + 1);

    size_t tempIndex = leftIsSmaller ? 0 : rightSize - 1;
    size_t bigArrIndex = leftIsSmaller ? mid + 1 : mid;
    size_t destIndex = leftIsSmaller ? leftStart : rightEnd;
    size_t gallopThreshold = 7;
    size_t gallopCount = 0;
    bool isTempArraySource = true;

    while ((leftIsSmaller && tempIndex < tempArr.size() && bigArrIndex <= rightEnd) || (!leftIsSmaller && tempIndex != SIZE_MAX && bigArrIndex >= leftStart)) {        
        if (leftIsSmaller) {
            if (tempArr[tempIndex] <= arr[bigArrIndex]) {
                arr[destIndex++] = tempArr[tempIndex++];
                gallopCount = (isTempArraySource) ? gallopCount + 1 : 1;
                isTempArraySource = true;
            }
            else {
                arr[destIndex++] = arr[bigArrIndex++];
                gallopCount = (!isTempArraySource) ? gallopCount + 1 : 1;
                isTempArraySource = false;
            }
        }
        else {
            if (tempArr[tempIndex] >= arr[bigArrIndex]) {
                arr[destIndex--] = tempArr[tempIndex--];
                gallopCount = (isTempArraySource) ? gallopCount + 1 : 1;
                isTempArraySource = true;
            }
            else {
                arr[destIndex--] = arr[bigArrIndex--];
                gallopCount = (!isTempArraySource) ? gallopCount + 1 : 1;
                isTempArraySource = false;
            }
        }

        if (gallopCount >= gallopThreshold) {
            size_t endRange = isTempArraySource
                ? gallopSearch(tempArr, arr[bigArrIndex], (leftIsSmaller ? tempIndex : 0), (leftIsSmaller ? tempArr.size() - 1 : tempIndex), leftIsSmaller)
                : gallopSearch(arr, tempArr[tempIndex], (leftIsSmaller ? bigArrIndex : leftStart), (leftIsSmaller ? rightEnd : bigArrIndex), leftIsSmaller);

            if (endRange != SIZE_MAX) {
                size_t copyCount;
                if (leftIsSmaller) {
                    copyCount = (endRange - (isTempArraySource ? tempIndex : bigArrIndex) + 1);
                    std::copy((isTempArraySource ? tempArr : arr).begin() + (isTempArraySource ? tempIndex : bigArrIndex), (isTempArraySource ? tempArr : arr).begin() + endRange + 1, arr.begin() + destIndex);
                    (isTempArraySource ? tempIndex : bigArrIndex) = endRange + 1;
                    destIndex = (leftIsSmaller ? destIndex + copyCount : destIndex - copyCount);
                }

                else {
                    copyCount = (isTempArraySource ? tempIndex : bigArrIndex) - endRange + 1;
                    std::copy((isTempArraySource ? tempArr : arr).begin() + endRange, (isTempArraySource ? tempArr : arr).begin() + (isTempArraySource ? tempIndex : bigArrIndex) + 1, arr.begin() + destIndex - copyCount + 1);
                    (isTempArraySource ? tempIndex : bigArrIndex) = endRange - 1;
                    destIndex = (leftIsSmaller ? destIndex + copyCount : destIndex - copyCount);
                }
            }
        }
    }

    if (tempIndex >= 0 && tempIndex < tempArr.size()) {
        if (leftIsSmaller) {
            std::copy(tempArr.begin() + tempIndex, tempArr.end(), arr.begin() + destIndex);
        }
        else {
            std::copy(tempArr.begin(), tempArr.begin() + tempIndex + 1, arr.begin() + (destIndex - tempIndex));
        }
    }
}

template <typename T>
void TimSort<T>::sort(std::vector<T>& arr) 
{
    size_t n = arr.size();
    size_t minrun = getMinrun(n);
    std::stack<std::pair<size_t, size_t>> runStack;

    size_t i = 0;

    while (i < n) {
        size_t runStart = i;
        size_t runEnd = runStart + 1;

        bool isAscending = true;
        while (runEnd < n && ((isAscending && arr[runEnd] >= arr[runEnd - 1]) || (!isAscending && arr[runEnd] <= arr[runEnd - 1]))) {
            if (arr[runEnd] < arr[runEnd - 1]) isAscending = false;
            ++runEnd;
        }

        if (!isAscending) {
            std::reverse(arr.begin() + runStart, arr.begin() + runEnd);
        }

        if (runEnd - runStart < minrun) {
            runEnd = std::min(runStart + minrun, n);
        }

        insertionSort(arr, runStart, runEnd - 1);
        runStack.push({ runStart, runEnd - runStart });
        
        while (runStack.size() >= 3) {
            auto x = runStack.top(); runStack.pop();
            auto y = runStack.top(); runStack.pop();
            auto z = runStack.top(); runStack.pop();

            if (z.second > (y.second + x.second) && y.second > x.second) {
                runStack.push(z);
                runStack.push(y);
                runStack.push(x);
                break;
            }
            if (x.second < z.second) {
                merge(arr, y.first, y.first + y.second - 1, x.first + x.second - 1);
                runStack.push(z);
                runStack.push({ y.first, y.second + x.second });
            }
            else {
                merge(arr, z.first, z.first + z.second - 1, y.first + y.second - 1);
                runStack.push({ z.first, z.second + y.second });
                runStack.push(x);
            }
        }

        i = runEnd;
    }
    
    while (runStack.size() >= 2) {
        auto x = runStack.top(); runStack.pop();
        auto y = runStack.top(); runStack.pop();

        std::vector<T> checkX;
        checkX.assign(arr.begin() + x.first, arr.begin() + x.first + x.second);
        std::vector<T> checkY;
        checkY.assign(arr.begin() + y.first, arr.begin() + y.first + y.second);

        merge(arr, y.first, y.first + y.second - 1, x.first + x.second - 1);
        runStack.push({ y.first, y.second + x.second });
    }

}

#endif // TIMSORT_H
