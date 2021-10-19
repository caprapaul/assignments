package sdi.exam.services;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import sdi.exam.models.Example;
import sdi.exam.repositories.IExampleRepository;

import java.util.List;

@Service
public class ExampleService implements ICrudService<Example> {
    @Autowired
    private IExampleRepository examples;

    @Override
    public List<Example> findAll() {
        return examples.findAll();
    }
}
