import { HttpClient } from '@angular/common/http';
import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Observable } from 'rxjs';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.scss']
})
export class LoginComponent implements OnInit {
  model: any = {};

  constructor(private httpClient: HttpClient,
    private router: Router) { }

  ngOnInit() {
    sessionStorage.setItem('user', '');
  }

  login() {
    sessionStorage.setItem('user', this.model.username);
    this.router.navigate(['/data']);
  }
}
