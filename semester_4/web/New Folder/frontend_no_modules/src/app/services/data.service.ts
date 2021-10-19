import { Injectable } from '@angular/core';

import { HttpClient } from "@angular/common/http";

import { CRUDService } from './crud.service';
import { IUser, IUsers } from '../models/data.interface';
import { IAuction } from '../models/auction.interface';

@Injectable({
    providedIn: 'root'
})
export class DataService extends CRUDService<IAuction, IAuction[]> {
    constructor(httpClient: HttpClient) {
        super(httpClient, 'http://localhost:5000/api/auctions')
    }
}