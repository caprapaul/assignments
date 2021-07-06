package exam.dto;

import exam.models.BaseEntity;
import lombok.*;

import javax.persistence.Entity;

@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
@NoArgsConstructor
@AllArgsConstructor
@Data
public class AddressDTO extends BaseDTO {
    private String city;
    private String street;
}
