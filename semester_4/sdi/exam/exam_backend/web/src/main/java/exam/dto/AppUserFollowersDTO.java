package exam.dto;

import lombok.*;


@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
@NoArgsConstructor
@AllArgsConstructor
@Data
public class AppUserFollowersDTO extends AppUserDTO {
    private FollowersDTO followers;
}
