package exam;

import exam.config.CoreConfig;
import exam.services.AppUserService;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Import;

@SpringBootApplication(scanBasePackages = "exam")
@Import(CoreConfig.class)
//@Import(AppUserService.class)
@ComponentScan({"exam.*"})
public class ExamApplication {

    public static void main(String[] args) {
        SpringApplication.run(ExamApplication.class, args);
    }

}
