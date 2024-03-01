package by.andrew.share.model;

import lombok.Data;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.context.annotation.PropertySource;
import org.springframework.stereotype.Component;

@Data
@Component
@PropertySource("classpath:application.properties")
public final class ShareRequest {

    @Value("${symbol}")
    private String symbol;

    @Value("${apikey}")
    private String key;
}
