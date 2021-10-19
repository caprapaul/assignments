import { Component, OnInit } from '@angular/core';
import { IUser } from 'src/app/models/data.interface';
import { UserService } from 'src/app/services/users.service';

@Component({
  selector: 'data-list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.scss'],
})
export class ListComponent implements OnInit {
  data: IUser[];
  errorMessage: string;

  constructor(private service: UserService) {
    this.data = [];
    this.errorMessage = "";
  }

  ngOnInit(): void {
    this.getAll();
  }

  validate(user: IUser) {


    return true;
  }

  add(name: string, password: string) {
    this.errorMessage = "";
    const user: IUser = {
      id: -1,
      username: name,
      password: password
    };

    if (this.validate(user)) {
      this.service.getAll()
        .subscribe(
          data => {
            const maxId = Math.max.apply(Math, data.map((o) => o.id));
            this.data = data.sort((a, b) => a.id < b.id ? -1 : 1);

            user.id = maxId + 1;
            this.service.add(user).subscribe(_ => {
              this.getAll();
            });
          },
          error => this.errorMessage = error
        );
    }
  }

  getAll() {
    this.service.getAll()
      .subscribe(
        data => {
          console.log(data);
          this.data = data;
        },
        error => this.errorMessage = error
      );
  }

  update(id: string, name: string, password: string) {
    this.errorMessage = "";
    const user: IUser = {
      id: parseInt(id),
      username: name,
      password: password
    };

    if (this.validate(user)) {
      this.service.update(user)
        .subscribe(
          _ => {
            this.getAll();
          },
          error => this.errorMessage = error
        );
    }
  }

  delete(id: string) {
    this.service.delete(parseInt(id))
      .subscribe(
        _ => {
          this.getAll();
        },
        error => this.errorMessage = error);
  }

  filter(value: string) {
    this.service.filter(value)
      .subscribe(
        data => {
          this.data = data.sort((a, b) => a.id - b.id);
          //console.log(this.clients);
        },
        error => this.errorMessage = <any>error
      );
  }
}
