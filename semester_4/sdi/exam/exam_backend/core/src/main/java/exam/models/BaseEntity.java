package exam.models;

import lombok.*;

import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.MappedSuperclass;

import java.io.Serializable;


@NoArgsConstructor
@AllArgsConstructor
@Getter
@Setter
@ToString
@MappedSuperclass
public abstract class BaseEntity<ID extends Serializable> implements Serializable{
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private ID id;
}
