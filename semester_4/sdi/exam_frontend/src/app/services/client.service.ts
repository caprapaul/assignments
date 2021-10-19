import { Injectable } from '@angular/core';

import { HttpClient } from "@angular/common/http";

import { CRUDService } from './crud.service';
import { IClient, IClients } from '../models/client.interface';

@Injectable({
    providedIn: 'root'
})
export class ClientService extends CRUDService<IClient, IClients> {
    constructor(httpClient: HttpClient) {
        super(httpClient, 'http://localhost:8080/api/clients')
    }
}