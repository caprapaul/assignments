import { Injectable } from '@angular/core';

import { HttpClient } from "@angular/common/http";

import { CRUDService } from './crud.service';
import { IUser, IUsers } from '../models/user.interface';
import { Observable } from 'rxjs';

@Injectable({
    providedIn: 'root'
})
export class UserService extends CRUDService<IUser, IUsers> {
    constructor(httpClient: HttpClient) {
        super(httpClient, 'http://localhost:8080/api/users')
    }

    getOneWithPost(id: number): Observable<IUser> {
        return this.httpClient.post<IUser>(`${this.url}/${id}`, null);
    }
}