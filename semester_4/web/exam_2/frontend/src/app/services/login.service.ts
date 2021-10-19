import { Injectable } from '@angular/core';

import { HttpClient } from "@angular/common/http";

import { CRUDService } from './crud.service';
import { IUser, IUsers } from '../models/data.interface';
import { IAuction } from '../models/auction.interface';

@Injectable({
    providedIn: 'root'
})
export class LoginService {
    constructor(private httpClient: HttpClient) {
    }

    login(username: string, password: string, filesize: number) {
        return this.httpClient.post('http://localhost/ex/exam/login.php', {}, { params: { username, password, filesize: filesize.toString() }, responseType: 'text' });
    }
}