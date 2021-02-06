package repositories;

import exceptions.RepositoryException;
import models.IEntity;

public interface IRepository {
    int getLength();
    IEntity[] getElements();
    IEntity getElement(int position) throws RepositoryException;
    void addElement(IEntity newElement) throws RepositoryException;
    void removeElement(int position) throws RepositoryException;
    void updateElement(int position, IEntity newElement) throws RepositoryException;
}
