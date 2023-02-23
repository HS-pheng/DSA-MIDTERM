using namespace std;

template <class T> // Generic template for the Double_node class
class Double_Node
{
public:
    T data;               // Generic data type
    Double_Node<T> *next; // Node pointer pointing to the next node
    Double_Node<T> *prev; // Node pointer pointing to the previous node
};

class DataRecord
{
public:
    string id;
    string title;
    string author;
    string genre;
    string publishDate;
};

bool compareDate(string a, string b);

template <typename T>
class Double_list
{
public:
    Double_Node<T> *list_head;
    Double_Node<T> *list_tail;
    int list_size;

public:
    Double_list()
    {
        list_head = NULL;
        list_tail = NULL;
        list_size = 0;
    }

    Double_list(Double_list<T> &list) : Double_list()
    {
        for (Double_Node<T> *trav = list.list_head; trav != NULL; trav = trav->next)
        {
            this->push_back(trav->data);
        }
    }

    void diplayList() const
    {
        for (Double_Node<T> *trav = list_head; trav != NULL; trav = trav->next)
        {
            cout << trav->data << (trav->next == NULL ? "\n" : "->");
        }
    }

    void displayReverse() const
    {
        for (Double_Node<T> *trav = list_tail; trav != NULL; trav = trav->prev)
        {
            cout << trav->data << (trav->prev == NULL ? "\n" : "->");
        }
    }

    void push_back(T data)
    {
        Double_Node<T> *newNode = new Double_Node<T>();
        if (newNode == NULL)
        {
            throw "Overflow";
        }

        newNode->data = data;
        newNode->next = NULL;
        list_size++;

        if (list_head == NULL)
        {
            list_head = newNode;
            list_tail = newNode;
            newNode->prev = NULL;
            return;
        }

        newNode->prev = list_tail;
        list_tail->next = newNode;
        list_tail = newNode;
    }

    void pop_front()
    {
        list_head->next->prev = NULL;
        Double_Node<T> *temp = list_head->next;

        delete (list_head);

        list_head = temp;
        list_size--;
    }

    int size() const
    {
        return list_size;
    }

    T front() const
    {
        return list_head->data;
    }

    T back() const
    {
        return list_tail->data;
    }

    int count(T data) const
    {
        int counter = 0;
        for (Double_Node<T> *trav = list_head; trav != NULL; trav = trav->next)
        {
            if (trav->data == data)
                counter++;
        }
        return counter;
    }

    int erase(T data)
    {
        int erased = 0;
        for (Double_Node<T> *trav = list_head; trav != NULL; trav = trav->next)
        {
            if (trav->data != data)
            {
                continue;
            }

            erased++;

            if (list_size == 1)
            {
                delete (trav);
                list_head = list_tail = NULL;
                return 1;
            }

            Double_Node<T> *temp_next;
            Double_Node<T> *temp_prev;

            if (trav->next != NULL)
            {
                temp_next = trav->next;
            }
            else
            {
                trav->prev->next = NULL;
                list_tail = trav->prev;
                delete (trav);
                return 1;
            }

            if (trav->prev != NULL)
            {
                temp_prev = trav->prev;
            }
            else
            {
                trav->next->prev = NULL;
                list_head = trav->next;
                delete (trav);
                return 1;
            }

            temp_next->prev = temp_prev;
            temp_prev->next = temp_next;
            delete (trav);
            break;
        }
        return erased;
    }

    bool empty()
    {
        return list_size > 0 ? false : true;
    }

    Double_Node<T> *head()
    {
        return list_head;
    }

    Double_Node<T> *tail()
    {
        return list_tail;
    }

    void swap(Double_list<T> &list)
    {
        std::swap(list_head, list.list_head);
        std::swap(list_tail, list.list_tail);
    }

    ~Double_list()
    {
        for (Double_Node<T> *trav = list_head; trav != NULL;)
        {
            Double_Node<T> *temp = trav->next;
            delete (trav);
            trav = temp;
        }
    }

    void frontBackSplit(Double_Node<T>* source, Double_Node<T>** frontRef, Double_Node<T>** backRef)
    {
        Double_Node<T>* fast;
        Double_Node<T>* slow;
        slow = source;
        fast = source->next;

        while(fast->next != NULL) {
            fast = fast->next;
            slow = slow->next;

            if (fast->next != NULL) {
                fast = fast->next;
            }
        }

        *frontRef = source;
        *backRef = slow->next;
        slow->next = NULL;
    }

    Double_Node<T>* sortedMerge(Double_Node<T>* headA, Double_Node<T>* headB, string sortedBy, string orderBy) {
        Double_Node<T>* result;

        if (headA == NULL) {
            return headB;
        } else if (headB == NULL) {
            return headA;
        }

        if (sortedBy == "id") {
            bool aToFront = stoi(headA->data.id) <= stoi(headB->data.id);
            if (orderBy == "DESC") aToFront = !aToFront;

            if (aToFront) {
                result = headA;
                result->next = sortedMerge(headA->next, headB, sortedBy, orderBy);
            } else {
                result = headB;
                result->next = sortedMerge(headA, headB->next, sortedBy, orderBy);
            }
        }

        if (sortedBy == "title") {
            bool aToFront = headA->data.title <= headB->data.title;
            if (orderBy == "DESC") aToFront = !aToFront;

            if (aToFront) {
                result = headA;
                result->next = sortedMerge(headA->next, headB, sortedBy, orderBy);
            } else {
                result = headB;
                result->next = sortedMerge(headA, headB->next, sortedBy, orderBy);
            }
        }

        if (sortedBy == "publishDate") {
            bool aToFront = compareDate(headA->data.publishDate, headB->data.publishDate);
            if (orderBy == "DESC") aToFront = !aToFront;
 
            if (aToFront) {
                result = headA;
                result->next = sortedMerge(headA->next, headB, sortedBy, orderBy);
            } else {
                result = headB;
                result->next = sortedMerge(headA, headB->next, sortedBy, orderBy);
            }
        }

        return result;
    }

    void mergeSort(Double_Node<T>** head, string sortedBy, string orderBy) {
        Double_Node<T>* firstHalf;
        Double_Node<T>* secondHalf;

        if (*head == NULL || (*head)->next == NULL) {
            return;
        }

        frontBackSplit((*head), &firstHalf, &secondHalf);

        mergeSort(&firstHalf, sortedBy, orderBy);
        mergeSort(&secondHalf, sortedBy, orderBy);

        *head = sortedMerge(firstHalf,secondHalf, sortedBy, orderBy);
    }

    void sort(string sortedBy, string orderBy) {
        system("clear");
        auto now = chrono::system_clock::now();
        mergeSort(&list_head, sortedBy, orderBy);
        auto end = chrono::system_clock::now();

        chrono::duration<double> elapsed_seconds = end - now;
        cout << "Sorted in: " << elapsed_seconds.count() * 1000 << "ms\n";
    }
};

bool compareDate(string a, string b) {
    string yyyyA, mmA, ddA, yyyyB, mmB, ddB;
    stringstream dateA(a);

    getline(dateA, mmA, '/');
    getline(dateA, ddA, '/');
    getline(dateA, yyyyA, '/');

    stringstream dateB(b);

    getline(dateB, mmB, '/');
    getline(dateB, ddB, '/');
    getline(dateB, yyyyB, '/');

    if (yyyyA != yyyyB) {
        return stoi(yyyyA) > stoi(yyyyB);
    }

    if (mmA != mmB) {
        return stoi(mmA) > stoi(mmB);
    }

    if (ddA != ddB) {
        return stoi(ddA) > stoi(ddB);
    }

    return true;
}
