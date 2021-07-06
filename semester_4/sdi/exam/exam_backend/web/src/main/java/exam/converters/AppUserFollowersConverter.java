package exam.converters;

import exam.dto.AppUserFollowersDTO;
import exam.dto.FollowerDTO;
import exam.dto.FollowersDTO;
import exam.models.AppUser;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.util.stream.Collectors;

@Component
public class AppUserFollowersConverter extends BaseConverter<Long, AppUser, AppUserFollowersDTO> {
    @Autowired
    private FollowerConverter followerConverter;

    @Override
    public AppUser convertDTOToModel(AppUserFollowersDTO dto) {
        AppUser model = new AppUser();
        model.setId(dto.getId());
        model.setName(dto.getName());
        model.setFollowers(dto.getFollowers().getFollowers().stream().map(currentDto -> followerConverter.convertDTOToModel(currentDto)).collect(Collectors.toList()));

        return model;
    }

    @Override
    public AppUserFollowersDTO convertModelToDTO(AppUser model) {
        AppUserFollowersDTO dto = new AppUserFollowersDTO();
        dto.setId(model.getId());
        dto.setName(model.getName());
        FollowersDTO followersDTO = new FollowersDTO(model.getFollowers().stream().map(currentModel -> followerConverter.convertModelToDTO(currentModel)).collect(Collectors.toList()));
        dto.setFollowers(followersDTO);

        return dto;
    }
}
