#pragma once

template<typename TElement>
class VectorIterator;

template<typename TElement>
class Vector
{
private:
    TElement *elements;
    int size;
    int capacity;

    void resize(int newCapacity);

    friend class VectorIterator<TElement>;

public:
    Vector();
    Vector(Vector<TElement> const& source);
    ~Vector();

    VectorIterator<TElement> Iterator();

    void Push(TElement element);
    TElement Pop();
    void Insert(int index, TElement element);
    void Remove(int index);

    TElement& operator[](int index);
    Vector<TElement>& operator=(Vector<TElement> const& source);

    int Size();
    int Capacity();
};

template<typename TElement>
inline void Vector<TElement>::resize(int newCapacity)
{
    TElement *newElements = new TElement[newCapacity];

    for (int i = 0; i < this->size; i++)
    {
        newElements[i] = this->elements[i];
    }

    delete[] this->elements;
    this->elements = newElements;
    this->capacity = newCapacity;
}

template<typename TElement>
inline Vector<TElement>::Vector()
{
    this->capacity = 5;
    this->size = 0;
    elements = new TElement[this->capacity];
}

template<typename TElement>
inline Vector<TElement>::Vector(Vector<TElement> const& source)
{
    this->elements = new TElement[source.capacity];

    this->size = source.size;
    this->capacity = source.capacity;

    for (int i = 0; i < this->size; ++i)
    {
        this->elements[i] = source.elements[i];
    }
}

template<typename TElement>
inline Vector<TElement>::~Vector()
{
    delete[] elements;
}

template<typename TElement>
inline VectorIterator<TElement> Vector<TElement>::Iterator()
{
    return VectorIterator<TElement>(*this);
}

template<typename TElement>
inline void Vector<TElement>::Push(TElement element)
{
    if (this->size >= this->capacity)
    {
        resize(2 * this->capacity);
    }

    this->elements[this->size] = element;
    this->size++;
}

template<typename TElement>
inline TElement Vector<TElement>::Pop()
{
    this->size--;
    return this->elements[this->size];
}

template<typename TElement>
inline void Vector<TElement>::Insert(int index, TElement element)
{
    if (this->size >= this->capacity)
    {
        resize(2 * this->capacity);
    }

    for (int i = this->size - 1; i >= index; i--)
    {
        this->elements[i + 1] = this->elements[i];
    }

    this->elements[index] = element;
    this->size++;
}

template<typename TElement>
inline void Vector<TElement>::Remove(int index)
{
    for (int i = index; i < this->size - 1; i++)
    {
        this->elements[i] = this->elements[i + 1];
    }

    this->size--;
}

template<typename TElement>
inline TElement& Vector<TElement>::operator[](int index)
{
    return this->elements[index];
}

template<typename TElement>
inline Vector<TElement>& Vector<TElement>::operator=(Vector<TElement> const& source)
{
    if (this == &source)
    {
        return *this;
    }

    delete[] this->elements;
    this->elements = new TElement[source.capacity];

    this->size = source.size;
    this->capacity = source.capacity;

    for (int i = 0; i < this->size; ++i)
    {
        this->elements[i] = source.elements[i];
    }

    return *this;
}

template<typename TElement>
inline int Vector<TElement>::Size()
{
    return this->size;
}

template<typename TElement>
inline int Vector<TElement>::Capacity()
{
    return this->capacity;
}
