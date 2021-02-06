package repositories;

import exceptions.RepositoryException;
import models.IEntity;

public class ArrayRepository implements IRepository {
    private IEntity[] elements;
    private int capacity;
    private int length;

    public ArrayRepository(int maxCapacity) {
        this.elements = new IEntity[maxCapacity];
        this.capacity = maxCapacity;
        this.length = 0;
    }

    @Override
    public int getLength() {
        return this.length;
    }

    @Override
    public IEntity[] getElements() {
        return this.elements;
    }

    @Override
    public IEntity getElement(int position) throws RepositoryException {
        if(position < 0 || position >= this.capacity) {
            throw new RepositoryException("Invalid position");
        }

        return this.elements[position];
    }

    @Override
    public void addElement(IEntity newElement) throws RepositoryException {
        if(this.length >= this.capacity) {
            throw new RepositoryException("Repository size limit reached");
        }

        this.elements[this.length] = newElement;
        this.length += 1;
    }

    @Override
    public void removeElement(int position) throws RepositoryException {
        if(position < 0 || position >= this.capacity) {
            throw new RepositoryException("Invalid position");
        }

        for (int i = position; i < this.length; i++) {
            this.elements[i] = this.elements[i + 1];
        }
        this.length--;
    }

    @Override
    public void updateElement(int position, IEntity newElement) throws RepositoryException {
        if(position < 0 || position >= this.capacity) {
            throw new RepositoryException("Invalid position");
        }

        this.elements[this.length] = newElement;
    }
}
