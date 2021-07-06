package exam.converters;

import exam.dto.AppUserDTO;
import exam.models.AppUser;
import org.springframework.stereotype.Component;

@Component
public class AppUserConverter extends BaseConverter<Long, AppUser, AppUserDTO> {
    @Override
    public AppUser convertDTOToModel(AppUserDTO dto) {
        AppUser model = new AppUser();
        model.setId(dto.getId());
        model.setName(dto.getName());

        return model;
    }

    @Override
    public AppUserDTO convertModelToDTO(AppUser model) {
        AppUserDTO dto = new AppUserDTO();
        dto.setId(model.getId());
        dto.setName(model.getName());

        return dto;
    }
}
