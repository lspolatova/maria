// шаблон стек
#include <iostream>
#include <cassert> // библиотека для assert
#include <iomanip>  // для setw

using namespace std;

// Интерфейс шаблона класса 
template <typename T>   

class Stack
{

private:

    T *stackPtr;           
    int size;              // максимальное количество элементов в стеке
    T top;                 // номер текущего элемента стека
                                      
public:
    
    Stack(int = 10);        // по умолчанию размер стека равен 10 элементам
    ~Stack();               // деструктор
    bool push(const T);   // поместить элемент в стек
    bool pop();             // удалить из стека элемент
    void printStack();      // Вывод стека
};
 
int main()
{
    Stack <int> myStack(5);
 
    // заполняем стек
    cout << "Введите 5 элементов в стек: \n";
    int ct = 0;
    while (ct++ != 5)
    {
        int temp;
        cin >> temp;
        myStack.push(temp);
    }
 
    cout << "\nЭлементы стека: \n";
    myStack.printStack(); // вывод стека на экран
 
    cout << "\nУдаляем два элемента из стека:\n";
 
    myStack.pop(); // удаляем 1 элемент из стека
    myStack.pop(); // удаляем 2 элемент из стека
    cout << "Элементы стека: \n";
    myStack.printStack(); // вывод стека на экран
 
    return 0;
}
 
// конструктор стека
template <typename T>
Stack<T>::Stack(int s)
{
    size = s > 0 ? s: 10;   // инициализировать размер стека
    stackPtr = new T[size]; // выделить память под стек
    top = -1;               // значение -1 говорит о том, что стек пуст
}
 
// деструктор стека
template <typename T>
Stack<T>::~Stack()
{
    delete [] stackPtr; // удаляем стек
}
 
template <typename T>
bool Stack<T>::push(const T value)
{
    if (top == size - 1)
        return false; // стек полон
 
    top++;
    stackPtr[top] = value; 
 
    return true; 
}
 
template <typename T>

bool Stack<T>::pop()
{
    if (top == - 1)
        return false; // стек пуст
 
    stackPtr[top] = 0; // удаляем элемент из стека
    top--;
 
    return true; // успешное выполнение операции
}
 
// вывод стека на экран
template <typename T>
void Stack<T>::printStack()
{
    for (int ix = size -1; ix >= 0; ix--)
        cout << setw(5) << stackPtr[ix] << endl;
}


