package exam.config;

import org.springframework.boot.autoconfigure.domain.EntityScan;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.data.jpa.repository.config.EnableJpaRepositories;

@Configuration
@EntityScan(basePackages = "exam.models")
@EnableJpaRepositories(basePackages = "exam.*")
@ComponentScan({"exam.*"})
public class CoreConfig {
}
