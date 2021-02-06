#pragma once
#include <vector>
#include <functional>
#include <exception>

class RepositoryException : public std::exception {
private:
    char const* message;

public:
    RepositoryException(char const* message);

    virtual char const* what() const throw();
};

template <typename TElement>
class Repository
{
public:
    virtual ~Repository() {};

    virtual void Add(TElement element) = 0;
    virtual void RemoveIf(std::function<bool(TElement)> condition) = 0;
    virtual std::vector<TElement> FindIf(std::function<bool(TElement)> condition) = 0;
    virtual TElement FindFirst(std::function<bool(TElement)> condition) = 0;
    virtual void UpdateFirst(std::function<bool(TElement)> condition, TElement newElement) = 0;
    virtual void RemoveFirst(std::function<bool(TElement)> condition) = 0;
    virtual std::vector<TElement> GetAll() = 0;
    virtual TElement GetNext(std::function<bool(TElement)> condition) = 0;
    virtual void Clear() = 0;
};
