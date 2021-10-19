import { Injectable } from '@angular/core';

import { HttpClient } from "@angular/common/http";

import { CRUDService } from './crud.service';
import { IWebDomain, IWebDomains } from '../models/web-domain.interface';

@Injectable({
    providedIn: 'root'
})
export class WebDomainService extends CRUDService<IWebDomain, IWebDomains> {
    constructor(httpClient: HttpClient) {
        super(httpClient, 'http://localhost:8080/api/domains')
    }
}