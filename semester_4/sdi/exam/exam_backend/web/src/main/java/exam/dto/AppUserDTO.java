package exam.dto;

import lombok.*;


@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
@NoArgsConstructor
@AllArgsConstructor
@Data
public class AppUserDTO extends BaseDTO {
    private String name;
}
