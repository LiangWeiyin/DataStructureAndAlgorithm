#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#define N 20
using namespace std;

void swap(vector<int>& nums, int i, int j) {
	int temp = nums[i];
	nums[i]  = nums[j];
	nums[j]  = temp;
}

// 从节点 i 向下做 heapify, 堆的大小为 n, n 不是 nums.size()
void heapify(vector<int>& nums, int i, int n) {
	if (i >= n) {
		return ;
	}

	int lchild     = 2 * i + 1;
	int rchild     = 2 * i + 2;
	int indexOfMax = i;

	if (lchild < n && nums[lchild] > nums[indexOfMax]) {
		indexOfMax = lchild;
	}
	if (rchild < n && nums[rchild] > nums[indexOfMax]) {
		indexOfMax = rchild;
	}
	if (indexOfMax != i) {
		swap(nums, i, indexOfMax);
		heapify(nums, indexOfMax, n);
	}
}

// 构建堆
// 从最后一个叶子节点开始做heapify, 一层做完之后再往上
// 确保子树已经是堆
void build_heap(vector<int>& nums) {
	int n = nums.size();
	int last_node = n - 1;
	int parent    = (last_node - 1) / 2;
	for (int i = parent; i >= 0; --i) {
		heapify(nums, i, n);
	} 
}

void heap_sort(vector<int>& nums) {
	int n = nums.size();
	// 构建一个堆
	build_heap(nums);

	for (int i = n - 1; i >= 0; --i) {
		// 把堆顶元素拿到"最后"
		swap(nums, 0, i);
		// 将堆的大小减 1, 重新调整堆
		heapify(nums, 0, i);
	}
}

void init_arr(vector<int>& nums) {
	int n = nums.size();
	for (int i = 0; i < n; ++i) {
		// 1 ~ 100 的随机数
		nums[i] = 1 + (rand() % 100);
	}
}

void print_arr(vector<int>& nums) {
	int n = nums.size();
	for (int i = 0; i < n; ++i) {
		cout << nums[i] << " ";
	}
	cout << endl;
}

int main() {
	srand(static_cast<unsigned int>(time(NULL)));
	vector<int> nums(N);
	init_arr(nums);
	print_arr(nums);
	heap_sort(nums);
	print_arr(nums);
	
	return 0;
}