#include <iostream> 
using namespace std; 

// Функция обмена значений между двумя переменными
void swap(int* a, int* b) 
{ 
	int temp = *a; 
	*a = *b; 
	*b = temp; 
} 

// Функция разделения массива на три части с использованием двух опорных элементов
int partition(int* arr, int low, int high, int* lp) 
{ 
	// Упорядочиваем левый и правый пивоты
	if (arr[low] > arr[high]) 
		swap(&arr[low], &arr[high]); 

	// Инициализация индексов для левого пивота (lp) и правого пивота (g)
	int j = low + 1; 
	int g = high - 1, k = low + 1, p = arr[low], q = arr[high]; 

	// Проход по массиву и разделение на три части
	while (k <= g) { 
		// Если элемент меньше левого пивота
		if (arr[k] < p) { 
			swap(&arr[k], &arr[j]); 
			j++; 
		} 
		// Если элемент больше или равен правому пивоту
		else if (arr[k] >= q) { 
			while (arr[g] > q && k < g) 
				g--; 
			swap(&arr[k], &arr[g]); 
			g--; 
			// Если элемент меньше левого пивота, то меняем его местами с j-м элементом
			if (arr[k] < p) { 
				swap(&arr[k], &arr[j]); 
				j++; 
			} 
		} 
		k++; 
	} 

	// Уменьшаем j и увеличиваем g
	j--; 
	g++; 

	// Обмен местами левого и правого пивотов с их окончательными позициями
	swap(&arr[low], &arr[j]); 
	swap(&arr[high], &arr[g]); 

	*lp = j; // Возвращаем позицию левого пивота

	return g; // Возвращаем позицию правого пивота
} 

// Рекурсивная функция для сортировки массива методом Dual-Pivot QuickSort
void DualPivotQuickSort(int* arr, int low, int high) 
{ 
	if (low < high) { 
		int lp, rp; 
		rp = partition(arr, low, high, &lp); // Получаем позиции левого и правого пивотов
		DualPivotQuickSort(arr, low, lp - 1); // Сортируем левую часть
		DualPivotQuickSort(arr, lp + 1, rp - 1); // Сортируем среднюю часть
		DualPivotQuickSort(arr, rp + 1, high); // Сортируем правую часть
	} 
} 

// Функция main для тестирования алгоритма
int main() 
{ 
	int arr[] = { 24, 8, 42, 75, 29, 77, 38, 57 }; 
	DualPivotQuickSort(arr, 0, 7); 
	cout << "Отсортированный массив: "; 
	for (int i = 0; i < 8; i++) 
		cout << arr[i] << " "; 
	cout << endl; 
} 

