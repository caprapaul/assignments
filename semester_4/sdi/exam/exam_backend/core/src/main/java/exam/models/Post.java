package exam.models;

import lombok.*;

import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.ManyToOne;
import javax.persistence.OneToMany;
import java.util.List;

@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
@NoArgsConstructor
@AllArgsConstructor
@Data@Entity
public class Post extends BaseEntity<Long> {
    private String title;
    private String content;
    @ManyToOne(fetch = FetchType.LAZY)
    private AppUser appUser;
    @OneToMany(fetch = FetchType.LAZY)
    private List<Comment> comments;
}
