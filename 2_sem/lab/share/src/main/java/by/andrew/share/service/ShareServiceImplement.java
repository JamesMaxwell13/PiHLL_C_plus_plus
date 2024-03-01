package by.andrew.share.service;

import by.andrew.share.model.CompanyShare;
import by.andrew.share.model.ShareRequest;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.web.client.RestTemplate;

@Service
public class ShareServiceImplement implements ShareService {
    @Value("${apikey}")
    private String key;

    @Override
    public CompanyShare getShareRequest(String symbol) {
        //working: https://financialmodelingprep.com/api/v3/otc/real-time-price/AAPL?apikey=E9VH8iPg4Gcb7BtBusZjiZ1cZrv4Lshz
        String getUrl = "https://financialmodelingprep.com/api/v3/otc/real-time-price/{symbol}?apikey={key}";
        RestTemplate restTemplate = new RestTemplate();
        ResponseEntity<CompanyShare[]> responseEntity = restTemplate.getForEntity(getUrl, CompanyShare[].class);
        CompanyShare[] shareResponse = responseEntity.getBody();
        if (shareResponse != null && shareResponse.length == 1) {
            return shareResponse[0];
        } else {
            return null;
        }
    }
}
