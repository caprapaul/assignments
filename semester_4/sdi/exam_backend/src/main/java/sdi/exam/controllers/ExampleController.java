package sdi.exam.controllers;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;
import sdi.exam.models.Example;
import sdi.exam.services.ExampleService;

import java.util.List;

@RestController
@CrossOrigin(origins = "http://localhost:4200")
public class ExampleController {
    public static final Logger log = LoggerFactory.getLogger(ExampleController.class);

    @Autowired
    private ExampleService service;

    @GetMapping(value = "/examples")
    public List<Example> getExamples() {
        log.trace("getExamples - method entered");
        return service.findAll();
    }
}
