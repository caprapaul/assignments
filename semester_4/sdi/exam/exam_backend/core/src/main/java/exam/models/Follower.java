package exam.models;

import lombok.*;

import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.ManyToOne;
import javax.persistence.OneToOne;

@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
@NoArgsConstructor
@AllArgsConstructor
@Data@Entity
public class Follower extends BaseEntity<Long> {
    private String name;
    private String birthday;
    @OneToOne(fetch = FetchType.LAZY)
    private Address address;
    @ManyToOne(fetch = FetchType.LAZY)
    private AppUser appUser;
}
