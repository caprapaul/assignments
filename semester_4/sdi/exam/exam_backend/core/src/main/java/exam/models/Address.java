package exam.models;

import lombok.*;

import javax.persistence.Entity;

@EqualsAndHashCode(callSuper = true)
@ToString(callSuper = true)
@NoArgsConstructor
@AllArgsConstructor
@Data@Entity
public class Address extends BaseEntity<Long> {
    private String city;
    private String street;
}
