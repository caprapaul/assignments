import { Inject, Injectable } from '@angular/core';

import { HttpClient } from '@angular/common/http';

import { Observable } from 'rxjs';
import { IBaseEntities, IBaseEntity } from '../models/base-entity.interface';
import { mergeMap } from 'rxjs/operators';


export abstract class CRUDService<SingleType extends IBaseEntity, ArrayType extends IBaseEntities<SingleType>> {
    constructor(private httpClient: HttpClient, private url: string) {
        this.url = url;
    }

    add(item: SingleType) {
        return this.httpClient.post<SingleType>(this.url, item);
    }

    getAll(): Observable<ArrayType> {
        return this.httpClient.get<ArrayType>(this.url + `?username=${sessionStorage.getItem('user')}`);
    }

    getOne(id: number): Observable<SingleType> {
        return this.httpClient.get<SingleType>(`${this.url}/${id}`);
    }

    update(item: SingleType) {
        return this.httpClient.put<SingleType>(this.url, item);
    }

    delete(id: number) {
        return this.httpClient.delete<SingleType>(`${this.url}/${id}`);
    }

    filter<ParameterType>(value: ParameterType): Observable<ArrayType> {
        return this.httpClient
            .get<ArrayType>(`${this.url}/filter/${value}`);
    }
}