package sdi.exam.models;

import lombok.Data;
import lombok.EqualsAndHashCode;

import javax.persistence.Entity;

@EqualsAndHashCode(callSuper = true)
@Data
@Entity
public class Example extends BaseEntity<Long> {
    private String name;
}
