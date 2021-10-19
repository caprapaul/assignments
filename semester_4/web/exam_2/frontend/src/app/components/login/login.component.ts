import { HttpClient } from '@angular/common/http';
import { Component, OnInit } from '@angular/core';
import { Router } from '@angular/router';
import { Observable } from 'rxjs';
import { LoginService } from 'src/app/services/login.service';

@Component({
  selector: 'app-login',
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.scss']
})
export class LoginComponent implements OnInit {
  model: any = {};
  errorMessage: string = '';

  constructor(private service: LoginService,
    private router: Router) { }

  ngOnInit() {
    sessionStorage.setItem('user', '');
  }

  login() {
    this.service.login(this.model.username, this.model.password, this.model.filesize)
      .subscribe(
        _ => {
          console.log("logged in");
          sessionStorage.setItem('token', `${this.model.username}:${this.model.password}:${this.model.filesize}`);
          this.router.navigate(['/data']);
        },
        error => this.errorMessage = JSON.stringify(error)
      );;
  }
}
