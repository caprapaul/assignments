package sdi.exam.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import sdi.exam.models.Example;

public interface IExampleRepository extends JpaRepository<Example, Long> {
}
