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

	// ���룺�������Ĳ���ṹ
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
		//�������
		cur = new Node(val);
		if (parent->_value < val){
			parent->_right = cur;
		}
		else{
			parent->_left = cur;
		}
		cur->_parent = parent;

		// ����+����
		// ��ת��Ŀ�ľ��ǽ��߶�
		while (parent){
			// 1������parentƽ������
			if (parent->_left == cur){
				--parent->_bf;
			}
			else if (parent->_right == cur){
				++parent->_bf;
			}
			// 2���ж��Ƿ���Ҫ��������
			if (parent->_bf == 0){
				// -1/1  --> 0
				break;
			}
			else if (parent->_bf == 1 || parent->_bf == -1){
				// 0 --> 1/-1
				// �������ϸ���
				cur = parent;
				parent = parent->_parent;
			}
			// ��ʱ��Ҫ������������ֱ�Ӹ��£�����֮���ֱ�ӽ���������Ҫ�ٸ���
			else if (parent->_bf == -2 || parent->_bf == 2){
				// ����
				if (parent->_bf == -2 && cur->_bf == -1){
					// ��ߵ���߸ߣ�����
					RotateR(parent);
				}
				else if (parent->_bf == 2 && cur->_bf == 1){
					// �ұߵ��ұ߸�
					RotateL(parent);
				}
				// ˫�������ƽ��������Ҫ����
				else if (parent->_bf == 2 && cur->_bf == -1){
					// �ұߵ���߸�
					RotateL(parent);
					RotateR(cur);
					// ����ƽ������
				}
				else if (parent->_bf == -2 && cur->_bf == 1){
					// ��ߵ��ұ߸�
					Node* subL = parent->_left;
					Node* subLR = subL->_right;
					RotateR(parent);
					RotateL(cur);
					if (subLR->_bf){
						// ����ƽ������
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

// �����
// ÿ���ڵ���ɫ
// ���һ���ڵ��Ǻ�ɫ�����������������Ǻ�ɫ
// ����ÿ��·������ɫ�ڵ���Ŀ���
// ��ɫ������������ɫ����������
// ���Ǻ�ɫ��
// ����·�������·�������ڣ��·�������·��������
// ȫ�ڣ���̣������䣺�

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

	// ���������
	bool insert(const pair<K, V>& val){
		// ������ֻ��һ��ͷ���
		if (_header->_parent == nullptr){
			// ������һ�����ڵ�
			Node* root = new Node(val);
			root->_color = BLACK;

			_header->_parent = root;
			root->_parent = _header;

			_header->_lfet = root;
			_header->_right = root;
		}
		// �ǿ���
		Node* cur = _header->_parent;
		Node* parent = nullptr;
		whiel(cur){
			parent = cur;
			// ���� key ֵ���бȽϣ�pair.first

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
		// 1������parentƽ������
		if (parent->_left == cur){
			--parent->_bf;
		}
		else{
			++parent->_bf;
		}
		// 2���ж��Ƿ���Ҫ�˳����߼������ϸ��»��ߵ���
		if (parent->_bf == 0){
			break;
		}
		else if (parent->_bf == 1 || parent->_bf == -1){
			cur = parent;
			parent = parent->_parent;
		}
		else if (parent->_bf == 2 || parent->_bf == -2){
			// ������
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


// memcpyʵ�ַ�ʽ
void* memcpy1(void* dst, const void* src, size_t len){
	if (NULL == dst || NULL == src){
		return NULL;
	}
	void* ret = dst;
	if (dst <= src || (char*)dst > (char*)src + len){
		// û���ڴ��ص����ӵ͵�ַ��ʼ����
		while (len--){
			*(char*)dst = *(char*)src;
			dst = (char*)dst + 1;
			src = (char*)src + 1;
		}
	}
	else{
		// ���ڴ��ص����Ӹߵ�ַ��ʼ����
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
	// û���ڴ��ص�����ǰ��󿽱�
	if (dst <= src || (char*)src + len < (char*)dst){
		// ��ǰ��󿽱�
		while (len--){
			*(char*)dst = *(char*)src;
			dst = (char*)dst + 1;
			src = (char*)src + 1;
		}
	}
	//���ڴ��ص����Ӻ���ǰ����
	else{
		//�Ӻ���ǰ����
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
// ���鼯������Ϊ���ҵ�ͬһ����Ԫ��
class UnionFindSet{
public:
	// ��ʼ��һ�����鼯�ṹ
	// ���� n ��ʾ�ڵ㷶Χ
	UnionFindSet(size_t n){
		// ��ʼ��ÿһ���ڵ㶼��˫��
		// ����ʼ��ÿһ���ڵ㶼��˫�ף���Ϊһ������ʱ��������Ǹ��ڵ�������ֻ��һ���ڵ�
		_v.resize(n,-1);
	}

	// �ҵ�ǰ�ڵ�ĸ�
	// ��һ��Ԫ�صı�ţ��ҵ���Ԫ�����ڼ��ϵ�����
	int FindRoot(int e1){
		while (_v[e1] >= 0){
			e1 = _v[e1];
		}
		return e1;
	}
	// ���鼯�ĺϲ�
	bool Union(int e1, int e2){
		int root1 = FindRoot(e1);
		int root2 = FindRoot(e2);
		// ����Ԫ����ͬһ�����ϾͲ����ٺϲ�
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
	// ��������
	for (int i = 1; i < sz; ++i){
		int end = i;
		// ����������
		int key = arr[end];
		int j = 0;
		for (j = end - 1; j >= 0 && arr[j]>key; --j){
			arr[j + 1] = arr[j];
		}
		arr[j + 1] = key;
	}
}
// ʱ�临�Ӷȣ��O(N^2) ���O(N) ƽ��O(N^2)
// �ռ临�Ӷȣ�O(1)->��������������
// �ȶ��ԣ��ȶ�
// �������жȣ�����������������㷨��Ӱ���Ƿ�ϴ󣩣�����
// ע��߽�����:<= >= < >�ȵ��÷���������
void isL(vector<int>& arr){
	int len = arr.size();
	for (int i = 0; i < len-1; ++i){
		int end = i;// ����Ԫ�ص����һ��λ��
		int key = arr[end + 1];
		// �ҵ���һ��С�� key ��λ��
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

// ʱ�临�Ӷȣ��O(N^1.3) ���O(N^1.3s) ƽ��O(N^1.3)
// �ռ临�Ӷȣ�O(1)->��������������
// �ȶ��ԣ����ȶ�������ʱ��ͬ���Ԫ�ز�һ�����Է�����ͬ����
// �������жȣ�����������������㷨��Ӱ���Ƿ�ϴ󣩣����У����ʾ��ǲ�������������У�
// shell �������߼������߼����鼴��
void shellSort(vector<int>& arr){
	int n = arr.size();
	// ͨ������gap�����߼�����
	// ���ڽ��в�������
	// ��ͬ���Ԫ�ؽ����������
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

// ѡ������
void slsort(vector<int>& arr){
	int sz = arr.size();
	for (int i = 0; i < sz; ++i){
		int start = i;
		int min = i;
		//��δ���������������Сֵ
		for (int j = start + 1; j < sz; ++j){
			if (arr[j] < arr[min])
				min = j;
		}
		swap(arr[start], arr[min]);
	}
}

// ���ȶ�����Ҫ�Ǵ��ڴ���ѡ����ǰ��Ĵ���
void yhselectsort(vector<int>& arr){
	int sz = arr.size();
	int beg = 0;
	int end = sz - 1;
	while (beg < end){
		//  ÿ��ѡһ�����ֵ����Сֵ
		int min = beg, max = beg;
		for (int i = beg + 1; i <= end; ++i){
			if (arr[i] < arr[min])
				min = i;
			// �˴��ֲ����ֵѡ����ǰ��ģ���˲��ȶ����������"="�����ȶ���.
			if (arr[i] > arr[max])
				max = i;
		}
		swap(arr[min], arr[beg]);
		// ���ֵλ�÷����˱仯�������Ҫ����
		if (beg == max) max = min;
		swap(arr[max], arr[end]);
		beg++;
		end--;
	}
}

// ������
// ���ϵ���
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


// ��������
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

// ʱ��Ч�ʣ����O(n^2) ���O(n^2) ƽ��O(n^2)
// �ռ�Ч�ʣ�O(1)
// ���ݲ����У�������ζ�Ҫ���б���
// �ȶ�
// ѡ������
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
//ϣ������
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