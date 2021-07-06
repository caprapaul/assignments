package exam.controllers;

import exam.converters.AppUserConverter;
import exam.dto.AppUserDTO;
import exam.models.AppUser;
import exam.services.AppUserService;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;


@RestController
@CrossOrigin(origins = "http://localhost:4200")
public class AppUserController {
    public static final Logger log = LoggerFactory.getLogger(AppUserController.class);

    @Autowired
    private AppUserService service;

    @Autowired
    private AppUserConverter converter;

    @PostMapping(value = "/users/{id}")
    public AppUserDTO getUser(@PathVariable("id") long id) {
        log.info("getUser - method entered: id - {}", id);
        AppUserDTO data = this.converter.convertModelToDTO(this.service.find(id));
        return data;
    }
}
