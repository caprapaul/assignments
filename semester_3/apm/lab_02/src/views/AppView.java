package views;

import controllers.Controller;
import exceptions.RepositoryException;
import models.Bird;
import models.Cow;
import models.Pig;
import repositories.ArrayRepository;
import repositories.IRepository;


// 4. La o ferma se cresc pasari, vaci si porci.
//  Sa se afiseze toate animalele care au greutatea
//  mai mare decit 3kg.
public class AppView {
    public static void main(String[] arg) {
        IRepository repository = new ArrayRepository(10);
        Controller controller = new Controller(repository);

        Pig p1 = new Pig(50);
        Cow c1 = new Cow(100);
        Cow c2 = new Cow(98);
        Bird b1 = new Bird(1);
        Bird b2 = new Bird(3);
        Bird b3 = new Bird(4);

        try {
            controller.addElement(p1);
            controller.addElement(c1);
            controller.addElement(c2);
            controller.addElement(b1);
            controller.addElement(b2);
            controller.addElement(b3);
            controller.removeElement(2);
        }
        catch (RepositoryException exception) {
            System.out.println(exception.toString());
        }

        String[] filteredResult = controller.filterItems(3);

        for(String element: filteredResult) {
            System.out.println(element);
        }
    }
}
