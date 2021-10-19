import { Injectable } from '@angular/core';

import { HttpClient } from "@angular/common/http";

import { CRUDService } from './crud.service';
import { IUser, IUsers } from '../models/data.interface';

@Injectable({
    providedIn: 'root'
})
export class UserService extends CRUDService<IUser, IUser[]> {
    constructor(httpClient: HttpClient) {
        super(httpClient, 'https://localhost:5001/api/users')
    }
}