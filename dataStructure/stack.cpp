#include <iostream>
using namespace std;

namespace testStack {
    //*************************************************************************
    template <typename T>
    struct node {
        T val;
        node* next;
        node(T v = 0): val(v), next(nullptr)
        {}
    };
    //*************************************************************************
    template <typename T>
    class myStack {

    public:
        myStack() : head(nullptr), tail(nullptr), count(0)
        {}
    public:
        //*************************************************************************
        bool push(T val) {

            node<T>* appendNode = new node<T>(val);
            if (appendNode == nullptr) {
                cout << "Memory allcation fail..." << endl;
                return false;
            }
            appendNode->next = tail;
            tail = appendNode;
            ++count;
            return true;
        }
        //*************************************************************************
        bool pop() {

            if (empty()) {
                cout << "pop fail, stack is already empty..." << endl;
                exit(-1);
            }

            node<T>* p = tail;
            tail = tail->next;
            delete p;
            --count;
            return true;
        }
        //*************************************************************************
        T top() const {

            if (empty()) {
                cout << "get element fail, stack is empty..." << endl;
                exit(-1);
            }

            return tail->val;
        }
        //*************************************************************************
        size_t size() const {

            return count;
        }
        //*************************************************************************
        bool empty() const {
        
            return head == tail;
        }
    private:
        node<T>* head;
        node<T>* tail;
        size_t count;
    };

    void myMain() {

        myStack<int> st;
        for (int i = 0; i < 10; ++i) {
            st.push(i * 2);
        }

        cout << st.empty() << endl;
        cout << st.size() << endl;
        cout << st.top() << endl;
        st.pop();
        for (int i = 0; i < 5; ++i) {
            st.pop();
        }
        st.push(999);

        cout << st.size() << endl;
        cout << st.top() << endl;

        int size = st.size();
        for (int i = 0; i < size; ++i) {
            cout << i << " " << endl;
            st.pop();
        }
        cout << st.top() << endl;
        st.pop();
    }
};




int main() {

    testStack::myMain();

    return 0;
}
