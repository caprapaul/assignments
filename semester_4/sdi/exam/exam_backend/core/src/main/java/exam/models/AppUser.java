package exam.models;

import lombok.*;

import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.OneToMany;
import javax.persistence.OneToOne;
import java.util.List;

@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
@NoArgsConstructor
@AllArgsConstructor
@Data
@Entity
public class AppUser extends BaseEntity<Long> {
    private String name;
    private String birthday;
    @OneToOne(fetch = FetchType.LAZY)
    private Address address;
    @OneToMany(fetch = FetchType.LAZY)
    private List<Follower> followers;
    @OneToMany(fetch = FetchType.LAZY)
    private List<Post> posts;
}
