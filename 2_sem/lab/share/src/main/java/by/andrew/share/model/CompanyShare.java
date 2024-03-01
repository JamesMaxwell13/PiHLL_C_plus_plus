package by.andrew.share.model;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;
import lombok.Data;

import java.time.LocalDate;

@Data
@JsonIgnoreProperties(ignoreUnknown = true)
public class CompanyShare {
    //@NonNull
    private Float prevClose;

    private Float high;

    private Float low;

    private Float open;

    private Float lastSalePrice;

    private String lastUpdated;

    private String symbol;
}
