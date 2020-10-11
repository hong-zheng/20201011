#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <vector>
#include <time.h>
#include <string.h>
using namespace std;

template<class T>
struct AVLNode{
	T _value;
	int _bf;
	AVLNode<T>* _left;
	AVLNode<T>* _right;
	AVLNode<T>* _parent;
	AVLNode(const T& val = T())
		:_value(0)
		, _bf(0)
		, _left(nullptr)
		, _right(nullptr)
		, _parent(nullptr){}
};

template<class T>
class AVLTree{
public:
	typedef AVLNode<T> Node;

	AVLTree() :_root(nullptr){}

	// 插入：搜索树的插入结构
	bool insert(const T& val){
		if (_root == nullptr){
			_root = new Node(val);
			return true;
		}
		Node* cur = _root;
		Node* parent = nullptr;
		while (cur){
			parent = cur;
			if (cur->_value == val){
				return false;
			}
			else if(cur->_value < val){
				cur = cur->_right;
			}
			else if (cur->_value > val){
				cur = cur->_left;
			}
		}
		//插入操作
		cur = new Node(val);
		if (parent->_value < val){
			parent->_right = cur;
		}
		else{
			parent->_left = cur;
		}
		cur->_parent = parent;

		// 更新+调整
		// 旋转的目的就是降高度
		while (parent){
			// 1、更新parent平衡因子
			if (parent->_left == cur){
				--parent->_bf;
			}
			else if (parent->_right == cur){
				++parent->_bf;
			}
			// 2、判断是否需要继续更新
			if (parent->_bf == 0){
				// -1/1  --> 0
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1){
				// 0 --> 1/-1
				// 继续向上更新
				cur = parent;
				parent = parent->_parent;
			}
			// 此时需要调整，并不能直接更新，调整之后就直接结束，不需要再更新
			else if (parent->_bf == -2 || parent->_bf == 2){
				// 调整
				if (parent->_bf == -2 && cur->_bf == -1){
					// 左边的左边高，右旋
					RotateR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == 1){
					// 右边的右边高
					RotateL(parent);
				}
				// 双旋的情况平衡因子需要更新
				else if (parent->_bf == 2 && cur->_bf == -1){
					// 右边的左边高
					RotateL(parent);
					RotateR(cur);
					// 调整平衡因子
				}
				else if (parent->_bf == -2 && cur->_bf == 1){
					// 左边的右边高
					Node* subL = parent->_left;
					Node* subLR = subL->_right;
					RotateR(parent);
					RotateL(cur);
					if (subLR->_bf){
						// 调整平衡因子
					}
				}
				break;
			}
		}
		return true;
	}
private:
	void RotateR(Node* parent){
		Node* subL = parent->_left;
		Node* subLR = subL->_right;
		
		subL->_right = parent;
		parent->_left = subLR;
		if (subLR)
			subLR->_parent = parent;
		if (parent == _root){
			_root = subL;
			subL->_parent = nullptr;
		}
		else{
			Node* g = parent->_parent;
			subL->_parent = g;
			if (g->_left == parent){
				g->_left = subL;
			}
			else if (g->_right == parent){
				g->_right = subL;
			}
		}
		parent->_parent = subL;
		parent->_bf = 0;
		subL->_bf = 0;
	}

	void RotateL(Node* parent){
		Node* subR = parent->_right;
		Node* subRL = subR->_left;

		subR->_left = parent;
		parent->_right = subRL;

		if (subRL)
			subRL->_parent = parent;

		if (_root == parent){
			subR = _root;
			subR->_parent = nullptr;
		}
		else{
			Node* g = parent->_parent;
			subR->_parent = g;
			if (g->_left = parent){
				g->_left = subR;
			}
			else{
				g->_right = subR;
			}
		}
		parent->_parent = subR;
		parent->_bf = subR->_bf = 0;
	}
private:
	Node* _root;
};

// 红黑树
// 每个节点红黑色
// 如果一个节点是红色，则它的两个孩子是黑色
// 对于每条路径，黑色节点数目相等
// 黑色可以连续，红色不可以连续
// 根是黑色的
// 如果最长路径与最短路径都存在，最长路径是最短路径的两倍
// 全黑：最短；红黑相间：最长

enum Color{
	BLACK,
	RED
};

template<class K,class V>
struct RBNode{
	pair<K, V> _value;
	Color _color;
	RBNode<K, V> _parent;
	RBNode<K, V> _left;
	RBNode<K, V> _right;

	RBNode(const pair<K, V>& value=pair<K,V>())
	:_value(value)
	,_color(RED)
	, _parent(nullptr)
	, _left(nullptr)
	, _right(nullptr)
	{}
};
template<class K,class V>
class RBTree{
public:
	typedef RBNode<K, V> Node;
	RBNode()
		:_header(new Node){
		_header->_left = _header->_right = _header;
	}

	// 红黑树插入
	bool insert(const pair<K, V>& val){
		// 空树：只有一个头结点
		if (_header->_parent == nullptr){
			// 创建第一个根节点
			Node* root = new Node(val);
			root->_color = BLACK;

			_header->_parent = root;
			root->_parent = _header;

			_header->_lfet = root;
			_header->_right = root;
		}
		// 非空树
		Node* cur = _header->_parent;
		Node* parent = nullptr;
		whiel(cur){
			parent = cur;
			// 按照 key 值进行比较，pair.first

		}
	}
private:
	Node* _header;
};
template<class T>
void tt(){
	typedef AVLNode<T> Node;
	Node* parent;
	Node* cur;

	while (parent){
		// 1、更新parent平衡因子
		if (parent->_left == cur){
			--parent->_bf;
		}
		else{
			++parent->_bf;
		}
		// 2、判断是否需要退出或者继续向上更新或者调整
		if (parent->_bf == 0){
			break;
		}
		else if (parent->_bf == 1 || parent->_bf == -1){
			cur = parent;
			parent = parent->_parent;
		}
		else if (parent->_bf == 2 || parent->_bf == -2){
			// 做调整
			break; 
		}
	}
}
int main(){
	cout << "zhenghong" << endl;
	system("pause");
	return 0;
}
void ttt(){
	char s[] = "1234567890";
	char* p1 = s;
	char* p2 = s + 2;
	memcpy(p2, p1, 5);
	printf("%s\n", p2);
	p1 = s;
	p2 = s + 2;
	memmove(p2, p1, 5);
	printf("%s\n", p2);
}


// memcpy实现方式
void* memcpy1(void* dst, const void* src, size_t len){
	if (NULL == dst || NULL == src){
		return NULL;
	}
	void* ret = dst;
	if (dst <= src || (char*)dst > (char*)src + len){
		// 没有内存重叠，从低地址开始复制
		while (len--){
			*(char*)dst = *(char*)src;
			dst = (char*)dst + 1;
			src = (char*)src + 1;
		}
	}
	else{
		// 有内存重叠，从高地址开始复制
		src = (char*)src + len - 1;
		dst = (char*)dst + len - 1;
		while (len--){
			*(char*)dst = *(char*)src;
			dst = (char*)dst - 1;
			src = (char*)src - 1;
		}
	}
	return dst;
}

void* mcpy(void* dst, void* src, size_t len){
	if (dst == NULL || src == NULL) return NULL;
	void* ret = dst;
	// 没有内存重叠：从前向后拷贝
	if (dst <= src || (char*)src + len < (char*)dst){
		// 从前向后拷贝
		while (len--){
			*(char*)dst = *(char*)src;
			dst = (char*)dst + 1;
			src = (char*)src + 1;
		}
	}
	//有内存重叠：从后向前拷贝
	else{
		//从后向前拷贝
		dst = (char*)dst + len - 1;
		src = (char*)src + len - 1;
		while (len--){
			*(char*)dst = *(char*)src;
			dst = (char*)dst - 1;
			src = (char*)src - 1;
		}
	}
	return dst;
}

void* memmove1(void* dest, const void* src, size_t n){

	return dest;
}
// 并查集：就是为了找到同一类别的元素
class UnionFindSet{
public:
	// 初始化一个并查集结构
	// 其中 n 表示节点范围
	UnionFindSet(size_t n){
		// 初始化每一个节点都是双亲
		// 当初始化每一个节点都是双亲，且为一棵树的时候，自身就是根节点且树上只有一个节点
		_v.resize(n,-1);
	}

	// 找当前节点的根
	// 给一个元素的编号，找到该元素所在集合的名称
	int FindRoot(int e1){
		while (_v[e1] >= 0){
			e1 = _v[e1];
		}
		return e1;
	}
	// 并查集的合并
	bool Union(int e1, int e2){
		int root1 = FindRoot(e1);
		int root2 = FindRoot(e2);
		// 两个元素在同一个集合就不用再合并
		if (root1 == root2) return false;
		_v[root1] += _v[root2];
		_v[root2] = root1;
		return true;
	}
private:
	vector<int> _v;
};

void display(vector<int>& arr){
	int sz = arr.size();
	for (int i = 0; i < sz; ++i){
		cout << arr[i] << " ";
	}
	cout << endl;
}
void ss(vector<int>& arr){
	int sz = arr.size();
	// [0,sz-2]
	for (int i = 0; i < sz - 1; ++i){
		int cur = arr[i];
		int curi = i;
		for (int j = i + 1; j < sz; ++j){
			if (arr[j] < cur){
				curi = j;
				cur = arr[j];
			}
		}
		if (curi != i){
			swap(arr[i], arr[curi]);
		}
	}
}

void is(vector<int>& arr){
	int sz = arr.size();
	// 插入排序
	for (int i = 1; i < sz; ++i){
		int end = i;
		// 待插入数据
		int key = arr[end];
		int j = 0;
		for (j = end - 1; j >= 0 && arr[j]>key; --j){
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = key;
	}
}
// 时间复杂度：最坏O(N^2) 最好O(N) 平均O(N^2)
// 空间复杂度：O(1)->常数个变量个数
// 稳定性：稳定
// 数据敏感度（数据有序与无序对算法的影响是否较大）：敏感
// 注意边界问题:<= >= < >等的用法及其意义
void isL(vector<int>& arr){
	int len = arr.size();
	for (int i = 0; i < len-1; ++i){
		int end = i;// 有序元素的最后一个位置
		int key = arr[end + 1];
		// 找到第一个小于 key 的位置
		while (end >= 0 && arr[end] > key){
			arr[end + 1] = arr[end];
			end--;
		}
		arr[end + 1] = key;
	}
}

void shells(vector<int>& arr){
	int sz = arr.size();
	int gap = sz / 2;
	while (gap >= 1){
		for (int i = gap; i < sz; ++i){
			int end = i-gap;
			int cur = arr[i];
			while (end >= 0 && arr[end] > cur){
				arr[end+gap] = arr[end];
				end -= gap;
			}
			arr[end + gap] = cur;
		}
		gap /= 2;
	}
}

// 时间复杂度：最坏O(N^1.3) 最好O(N^1.3s) 平均O(N^1.3)
// 空间复杂度：O(1)->常数个变量个数
// 稳定性：不稳定，分组时相同组的元素不一定可以分在相同的组
// 数据敏感度（数据有序与无序对算法的影响是否较大）：敏感（本质就是插入排序，因此敏感）
// shell 排序是逻辑排序，逻辑分组即可
void shellSort(vector<int>& arr){
	int n = arr.size();
	// 通过步长gap进行逻辑分组
	// 组内进行插入排序
	// 不同组的元素交替进行排序
	int gap = n / 2;
	while (gap >= 1){
		for (int i = 0; i < n - gap; ++i){
			int end = i;
			int key = arr[end + gap];
			while (end >= 0 && arr[end] > key){
				arr[end + gap] = arr[end];
				end -= gap;
			}
			arr[end + gap] = key;
		}
		gap /= 2;
	}
}

// 选择排序
void slsort(vector<int>& arr){
	int sz = arr.size();
	for (int i = 0; i < sz; ++i){
		int start = i;
		int min = i;
		//从未排序的数据中找最小值
		for (int j = start + 1; j < sz; ++j){
			if (arr[j] < arr[min])
				min = j;
		}
		swap(arr[start], arr[min]);
	}
}

// 不稳定：主要是大于处就选择了前面的大数
void yhselectsort(vector<int>& arr){
	int sz = arr.size();
	int beg = 0;
	int end = sz - 1;
	while (beg < end){
		//  每次选一个最大值和最小值
		int min = beg, max = beg;
		for (int i = beg + 1; i <= end; ++i){
			if (arr[i] < arr[min])
				min = i;
			// 此处局部最大值选的是前面的：因此不稳定，如果加上"="就是稳定的.
			if (arr[i] > arr[max])
				max = i;
		}
		swap(arr[min], arr[beg]);
		// 最大值位置发生了变化，因此需要更新
		if (beg == max) max = min;
		swap(arr[max], arr[end]);
		beg++;
		end--;
	}
}

// 堆排序
// 向上调整
void shiftUp(vector<int>& arr, int child){

}
void t(){
	void slsort(vector<int>& arr);
	vector<int> arr = { 239,8,7,251,9,0,87,54,39,8,789,1,36,40 };
	vector<int> arr1 = { 10, 2, 4, 1, 3, 6, 5, 12, 9, 10, 2 };
	display(arr1);
	yhselectsort(arr1);
	display(arr1);
}
void tt(){
	srand(time(NULL));
	int n;
	cin >> n;
	vector<int> arr;
	for (int i = 0; i < n; ++i){
		arr.push_back(rand() % 1000);
	}
	size_t beg = clock();
	shellSort(arr);
	size_t end = clock();
	cout << "sort :" << end - beg << endl;
	
	beg = clock();
	shellSort(arr);
	end = clock();
	cout << "after :" << end - beg << endl;
}
int main1(){
	t();

	system("pause");
	return 0;
}


// 插入排序
void isort(vector<int>& arr){
	int sz = arr.size();
	for (int i = 1; i < sz; ++i){
		int cur = arr[i];
		int end = i-1;
		while (end >= 0 && arr[end] > cur){
			arr[end + 1] = arr[end];
			--end;
		}
		arr[end + 1] = cur;
	}
}

// 时间效率：最好O(n^2) 最差O(n^2) 平均O(n^2)
// 空间效率：O(1)
// 数据不敏感：无论如何都要进行遍历
// 稳定
// 选择排序
void ssort(vector<int>& arr){
	int sz = arr.size();
	for (int i = 0; i < sz; ++i){
		int cur = arr[i];
		int curi = i;
		for (int j = i + 1; j < sz; ++j){
			if (arr[j] < cur){
				cur = arr[j];
				curi = j;
			}
		}
		if (curi != i){
			swap(arr[i], arr[curi]);
		}
	}
}
//希尔排序
void selsort(vector<int>& arr){
	int sz = arr.size();
	int gap = sz / 2;
	while (gap >= 1){
		for (int i = gap; i < sz; ++i){
			int end = i - gap;
			int cur = arr[i];
			while (end >= 0 && arr[end] > cur){
				arr[end + gap] = arr[end];
				end -= gap;
			}
			arr[end + gap] = cur;
		}
		gap /= 2;
	}
}