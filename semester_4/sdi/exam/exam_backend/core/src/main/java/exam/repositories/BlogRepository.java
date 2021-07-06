package exam.repositories;

import org.springframework.data.jpa.repository.JpaRepository;
import exam.models.BaseEntity;

import java.io.Serializable;

public interface BlogRepository<T extends BaseEntity<ID>, ID extends Serializable> extends JpaRepository<T, ID> {
}
