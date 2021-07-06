package exam.converters;

import exam.dto.BaseDTO;
import exam.models.BaseEntity;

import java.io.Serializable;

public interface Converter<Id extends Serializable, Model extends BaseEntity<Id>, DTO extends BaseDTO> {
    Model convertDTOToModel(DTO dto);

    DTO convertModelToDTO(Model model);
}
