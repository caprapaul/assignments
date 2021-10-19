package sdi.exam.services;

import java.util.List;

public interface ICrudService<T> {
    List<T> findAll();

}
