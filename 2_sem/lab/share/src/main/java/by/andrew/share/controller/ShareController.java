package by.andrew.share.controller;

import by.andrew.share.model.CompanyShare;
import by.andrew.share.service.ShareService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

@RestController
@RequestMapping("/api/shares")
public class ShareController {
    private final ShareService shareService;

    @Autowired
    public ShareController(ShareService shareService) {
        this.shareService = shareService;
    }

    @GetMapping
    public ResponseEntity<CompanyShare> getShareInfo(@RequestParam(value = "symbol") String symbol) {
        CompanyShare shareResponse = shareService.getShareRequest(symbol);
        return new ResponseEntity<CompanyShare>(shareResponse, HttpStatus.OK);
    }
}
