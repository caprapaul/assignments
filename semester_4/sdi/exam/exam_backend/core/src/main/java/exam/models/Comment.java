package exam.models;

import lombok.*;

import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.ManyToOne;

@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
@NoArgsConstructor
@AllArgsConstructor
@Data@Entity
public class Comment extends BaseEntity<Long> {
    private String text;
    @ManyToOne(fetch = FetchType.LAZY)
    private Post post;
}
