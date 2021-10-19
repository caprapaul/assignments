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
    sessionStorage.setItem('token', '');
  }

  login() {
    let url = `http://localhost:8080/api/login`;
    this.httpClient.post<Observable<boolean>>(url, {}, { params: { username: this.model.username, password: this.model.password } })
      .subscribe(isValid => {
        if (isValid) {
          sessionStorage.setItem('token', this.model.username + ':' + this.model.password);
          //localStorage.setItem('token', btoa(this.model.username + ':' + this.model.password));
          // this.appService.authenticated = true;
          this.router.navigate(['/data']);
        }
        else {
          alert("Authentication failed.")
        }
      });
  }
}
