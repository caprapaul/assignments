package exam.converters;

import exam.dto.FollowerDTO;
import exam.models.Follower;
import org.springframework.stereotype.Component;

@Component
public class FollowerConverter extends BaseConverter<Long, Follower, FollowerDTO> {
    @Override
    public Follower convertDTOToModel(FollowerDTO dto) {
        Follower model = new Follower();
        model.setId(dto.getId());
        model.setName(dto.getName());

        return model;
    }

    @Override
    public FollowerDTO convertModelToDTO(Follower model) {
        FollowerDTO dto = new FollowerDTO();
        dto.setId(model.getId());
        dto.setName(model.getName());

        return dto;
    }
}
