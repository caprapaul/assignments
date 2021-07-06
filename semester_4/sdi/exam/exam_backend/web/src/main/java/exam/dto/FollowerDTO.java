package exam.dto;

import lombok.*;

@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
@NoArgsConstructor
@AllArgsConstructor
@Data
public class FollowerDTO extends BaseDTO {
    private String name;
}
