import { Injectable } from '@angular/core';

import { HttpClient } from "@angular/common/http";

import { IFile } from '../models/file.interface';
import { Observable } from 'rxjs';

@Injectable({
    providedIn: 'root'
})
export class DataService {
    constructor(private httpClient: HttpClient) {
    }

    search(word: string): Observable<IFile[]> {
        return this.httpClient.get<IFile[]>('http://localhost/ex/exam/search-files.php', { params: { word } });
    }
}