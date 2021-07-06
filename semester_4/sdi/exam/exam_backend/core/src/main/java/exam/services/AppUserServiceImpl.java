package exam.services;

import exam.models.AppUser;
import exam.repositories.AppUserRepository;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service
public class AppUserServiceImpl implements AppUserService {
    public static final Logger log = LoggerFactory.getLogger(AppUserServiceImpl.class);

    @Autowired
    private AppUserRepository users;

    @Override
    public AppUser find(Long id) {
        log.info("find - method entered: id - {}", id);
        return users.findById(id).orElse(null);
    }

    @Override
    public AppUser findWithFollowers(Long id) {
        return null;
    }

    @Override
    public AppUser findWithPostsAndFollowers(Long id) {
        return null;
    }
}
