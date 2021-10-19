package sdi.exam;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.domain.EntityScan;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Import;
import sdi.exam.config.RepositoriesConfig;

@SpringBootApplication
@EntityScan(basePackages = "sdi.exam.models")
@Import(RepositoriesConfig.class)
@ComponentScan({"sdi.exam.*"})
public class ExamApplication {

    public static void main(String[] args) {
        SpringApplication.run(ExamApplication.class, args);
    }

}
