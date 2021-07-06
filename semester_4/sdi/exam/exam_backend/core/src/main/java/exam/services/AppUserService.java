package exam.services;

import exam.models.AppUser;

public interface AppUserService {
    AppUser find(Long id);
    AppUser findWithFollowers(Long id);
    AppUser findWithPostsAndFollowers(Long id);
}
