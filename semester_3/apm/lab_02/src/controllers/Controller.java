package controllers;

import exceptions.RepositoryException;
import models.IEntity;
import repositories.IRepository;

public class Controller {
    IRepository repository;

    public Controller(IRepository repository) {
        this.repository = repository;
    }

    public void addElement(IEntity newElement) throws RepositoryException {
        this.repository.addElement(newElement);
    }

    public void removeElement(int position) throws RepositoryException {
        this.repository.removeElement(position);
    }

    public String[] filterItems(int minimumWeight) {
        String[] filteredItems = new String[this.repository.getLength()];
        int count = 0;

        for(IEntity element: this.repository.getElements()) {
            if(element == null) {
                break;
            }

            if(element.getWeight() > minimumWeight) {
                filteredItems[count] = element.toString();
                count += 1;
            }
        }

        String[] result = new String[count];
        System.arraycopy(filteredItems, 0, result, 0, count);

        return result;
    }
}
