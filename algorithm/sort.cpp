#include <iostream>
#include <cstdlib> // rand() srand() 
#include <ctime>   // time() 
#include <vector>
#define  N 20
using namespace std;

// 归并排序
namespace test01 {	
	void merge(vector<int>& nums, vector<int>& temp, int left, int mid, int right) {
		int i = left;
		int j = mid + 1;
		int k = 0;
		while (i <= mid && j <= right) {
			if (nums[i] <= nums[j]) {
				temp[k++] = nums[i++];
			}
			else {
				temp[k++] = nums[j++];
			}
		}
		while (i <= mid) {
			temp[k++] = nums[i++];
		}
		while (j <= right) {
			temp[k++] = nums[j++];
		}
		int t = 0;
		while (t < k) {
			nums[left++] = temp[t++];
		}
	} 

	void merge_sort(vector<int>& nums, vector<int>& temp, int left, int right) {
		if (left < right) {
			int mid = left + (right - left) / 2;
			merge_sort(nums, temp, left, mid);
			merge_sort(nums, temp, mid + 1, right);
			merge(nums, temp, left, mid, right);
		}
	}

}

// 快速排序
namespace test02 {
	// 挖空法
	int partition(vector<int>& nums, int left, int right) {
		int val = nums[left];
		while (left < right) {
			while (left < right && nums[right] >= val) {
				--right;
			}
			nums[left] = nums[right];
			while (left < right && nums[left] <= val) {
				++left;
			}
			nums[right] = nums[left];
		}
		nums[left] = val;
		return left;
	}

	// 随机化 避免最坏情况(有序)
	int random_partition(vector<int>& nums, int left, int right) {
		// 生成一个 left ~ right 的随机下标
		// 与第一个元素交换位置
		int i = left + (rand() % (right - left + 1));
		int temp = nums[i];
		nums[i] = nums[left];
		nums[left] = temp;

		return partition(nums, left, right);
	}

	void quick_sort(vector<int>& nums, int left, int right) {
		if (left < right) {
			int p = random_partition(nums, left, right);
			quick_sort(nums, left, p);
			quick_sort(nums, p + 1, right);
		}
	}
}

// 冒泡排序
// 每一轮都把最大的冒到最后
namespace tese03 {
	void bubble_sort(vector<int>& nums) {
		int n = nums.size();
		for (int i = 0; i < n - 1; ++i) {
			bool is_sorted = true;
			for (int j = 0; j < n - i - 1; ++j) {
				if (nums[j] > nums[j + 1]) {
					int temp = nums[j];
					nums[j]  = nums[j + 1];
					nums[j + 1]  = temp;
					is_sorted = false;
				}
			}
			if (is_sorted) {
				return ;
			}
		}
	}
};

// 选择排序
// 每一轮选择最小的放在前面
namespace test04 {
	void select_sort(vector<int>& nums) {
		int n = nums.size();
		for (int i = 0; i < n - 1; ++i) {
			int minI = i;
			for (int j = i + 1; j < n; ++j) {
				if (nums[minI] > nums[j]) {
					minI = j;
				}
			}
			if (minI != i) {
				int temp   = nums[i];
				nums[i]    = nums[minI];
				nums[minI] = temp; 
			}
		}
	}
};

void init_arr(vector<int>& nums) {
	for (int i = 0; i < nums.size(); ++i) {
		nums[i] = 1 + (rand() % 100);
	}
}

void print_arr(vector<int>& nums) {
	for (int i = 0; i < nums.size(); ++i) {
		cout << nums[i] << " ";
	}
	cout << endl;
}

int main() {
	srand(time(NULL));
	vector<int> nums(N);
	// 归并排序辅助数组
	vector<int> temp(N);

	init_arr(nums);
	print_arr(nums);
	test01::merge_sort(nums, temp, 0, N - 1);
	// test02::quick_sort(nums, 0, N - 1);
	// tese03::bubble_sort(nums);
	// test04::select_sort(nums);
	print_arr(nums);
	return 0;
}