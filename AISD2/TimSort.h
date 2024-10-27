#ifndef TIMSORT_H
#define TIMSORT_H

#include <vector>
#include <stack>
#include <utility>
#include <algorithm>

template <typename T>
class TimSort {
public:
    size_t getMinrun(size_t n);
    void insertionSort(std::vector<T>& arr, size_t left, size_t right);
    void merge(std::vector<T>& arr, size_t leftStart, size_t mid, size_t rightEnd);
    size_t gallopSearch(const std::vector<T>& arr, T key, size_t start, size_t end, bool direction);
    bool isSorted(const std::vector<T>& arr);


public:
    void sort(std::vector<T>& arr);
};

template <typename T>
size_t TimSort<T>::getMinrun(size_t n) {
    size_t r = 0;
    while (n >= 64) {
        r |= n & 1;
        n >>= 1;
    }
    return n + r;
}

template <typename T>
void TimSort<T>::insertionSort(std::vector<T>& arr, size_t left, size_t right) {
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
bool TimSort<T>::isSorted(const std::vector<T>& arr) {
    for (size_t i = 1; i < arr.size(); ++i) {
        if (arr[i - 1] > arr[i]) {
            return false; // Найдено нарушение порядка
        }
    }
    return true; // Вектор отсортирован
}

/*
template <typename T>
size_t TimSort<T>::gallopSearch(const std::vector<T>& arr, T key, size_t start, size_t end, bool direction) {
    size_t idx = start;
    size_t step = 1;

    // Находим диапазон для бинарного поиска
    while (idx + step < end && ((direction && arr[idx + step] <= key) || (!direction && arr[idx + step] >= key))) {
        idx += step;
        step *= 2;
    }

    // Устанавливаем границы для бинарного поиска
    size_t left = idx; // Начинаем с текущего индекса
    size_t right = std::min(idx + step / 2, end); // Устанавливаем правую границу

    // Бинарный поиск в пределах найденного диапазона
    while (left < right) {
        size_t mid = left + (right - left) / 2;

        if ((direction && arr[mid] < key) || (!direction && arr[mid] > key)) {
            left = mid + 1;  // Ключ находится правее
        }
        else {
            right = mid;     // Ключ находится левее или на текущей позиции
        }
    }

    return left;
}
*/


template <typename T>
size_t TimSort<T>::gallopSearch(const std::vector<T>& arr, T key, size_t start, size_t end, bool direction) {
    size_t idx = start;
    size_t step = 1;

    while (idx + step < end && ((direction && arr[idx + step] <= key) || (!direction && arr[idx + step] >= key))) {
        step *= 2;
    }
    return std::lower_bound(arr.begin() + idx, arr.begin() + std::min(idx + step, end), key) - arr.begin();
}


/*
template<typename T>
void TimSort<T>::merge(std::vector<T>& arr, size_t leftStart, size_t mid, size_t rightEnd) {
    size_t leftSize = mid - leftStart + 1;  // Размер левой части
    size_t rightSize = rightEnd - mid;     // Размер правой части

    // Создаем временные векторы для левой и правой частей
    std::vector<T> leftArray(leftSize);
    std::vector<T> rightArray(rightSize);

    // Копируем данные во временные массивы
    for (size_t i = 0; i < leftSize; ++i) {
        leftArray[i] = arr[leftStart + i];
    }
    for (size_t j = 0; j < rightSize; ++j) {
        rightArray[j] = arr[mid + 1 + j];
    }

    // Слияние временных массивов обратно в arr
    size_t i = 0;    // Индекс для левой части
    size_t j = 0;    // Индекс для правой части
    size_t k = leftStart; // Индекс для основного массива

    while (i < leftSize && j < rightSize) {
        if (leftArray[i] <= rightArray[j]) {
            arr[k] = leftArray[i];
            ++i;
        }
        else {
            arr[k] = rightArray[j];
            ++j;
        }
        ++k;
    }

    // Копируем оставшиеся элементы левой части, если есть
    while (i < leftSize) {
        arr[k] = leftArray[i];
        ++i;
        ++k;
    }

    // Копируем оставшиеся элементы правой части, если есть
    while (j < rightSize) {
        arr[k] = rightArray[j];
        ++j;
        ++k;
    }
}
*/

template<typename T>
void TimSort<T>::merge(std::vector<T>& arr, size_t leftStart, size_t mid, size_t rightEnd) {
    size_t leftSize = mid - leftStart + 1;
    size_t rightSize = rightEnd - mid;

    //bool leftIsSmaller = (leftSize <= rightSize);
    
    //std::vector<T> tempArr = leftIsSmaller
      //  ? std::vector<T>(arr.begin() + leftStart, arr.begin() + mid + 1)
        //: std::vector<T>(arr.begin() + mid + 1, arr.begin() + rightEnd + 1);
        
    
    std::vector<T> tempArr = std::vector<T>(arr.begin() + leftStart, arr.begin() + mid + 1);
    //size_t tempIndex = 0, bigArrIndex = leftIsSmaller ? mid + 1 : leftStart;
    size_t tempIndex = 0, bigArrIndex = mid + 1;
    size_t destIndex = leftStart;
    size_t gallopThreshold = 7;
    size_t gallopCount = 0;
    bool isTempArraySource = true;

    while (tempIndex < tempArr.size() && bigArrIndex <= rightEnd ) {
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
        
        if (gallopCount >= gallopThreshold) {
            size_t endRange = isTempArraySource
                ? gallopSearch(tempArr, arr[bigArrIndex], tempIndex, tempArr.size(), true)
                : gallopSearch(arr, tempArr[tempIndex], bigArrIndex, rightEnd + 1, false);

            size_t copyCount = endRange - (isTempArraySource ? tempIndex : bigArrIndex);
            if (destIndex + copyCount <= arr.size()) {
                size_t srcStart = isTempArraySource ? tempIndex : bigArrIndex;
                size_t srcEnd = srcStart + copyCount;

                if (srcEnd > (isTempArraySource ? tempArr.size() : rightEnd + 1)) {
                    srcEnd = isTempArraySource ? tempArr.size() : rightEnd + 1;
                }

                std::copy((isTempArraySource ? tempArr : arr).begin() + srcStart,
                    (isTempArraySource ? tempArr : arr).begin() + srcEnd,
                    arr.begin() + destIndex);

                destIndex += (srcEnd - srcStart);
                if (isTempArraySource) {
                    tempIndex += (srcEnd - srcStart);
                }
                else {
                    bigArrIndex += (srcEnd - srcStart);
                }
            }
            else {
                size_t spaceAvailable = arr.size() - destIndex;
                size_t srcStart = isTempArraySource ? tempIndex : bigArrIndex;
                size_t validCopyCount = isTempArraySource ? tempArr.size() : rightEnd + 1 - srcStart;
                validCopyCount = std::min(spaceAvailable, validCopyCount);

                // Копируем элементы
                std::copy((isTempArraySource ? tempArr : arr).begin() + srcStart,
                    (isTempArraySource ? tempArr : arr).begin() + srcStart + validCopyCount,
                    arr.begin() + destIndex);

                destIndex += validCopyCount;
                if (isTempArraySource) {
                    tempIndex += validCopyCount;
                }
                else {
                    bigArrIndex += validCopyCount;
                }
            }

        }
    }
    
    if (tempIndex < tempArr.size()) {
        std::copy(tempArr.begin() + tempIndex, tempArr.end(), arr.begin() + destIndex);
    }

    else if (bigArrIndex <= rightEnd) {
        std::copy(arr.begin() + bigArrIndex, arr.begin() + rightEnd + 1, arr.begin() + destIndex);
    }
}

template <typename T>
void TimSort<T>::sort(std::vector<T>& arr) {
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
            else {
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
        }

        i = runEnd;
    }
    
    while (runStack.size() >= 2) {
        auto x = runStack.top(); runStack.pop();
        auto y = runStack.top(); runStack.pop();
        merge(arr, y.first, y.first + y.second - 1, x.first + x.second - 1);
        runStack.push({ y.first, y.second + x.second });
    }

}

#endif // TIMSORT_H
