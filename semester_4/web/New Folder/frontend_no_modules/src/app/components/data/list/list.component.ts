import { HttpClient } from '@angular/common/http';
import { Component, OnInit } from '@angular/core';
import { IAuction } from 'src/app/models/auction.interface';
import { DataService } from 'src/app/services/data.service';

@Component({
  selector: 'data-list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.scss'],
})
export class ListComponent implements OnInit {
  data: IAuction[];
  errorMessage: string;

  constructor(private service: DataService, private httpClient: HttpClient) {
    this.data = [];
    this.errorMessage = "";
  }

  ngOnInit(): void {
    this.getAll();
  }

  // add(name: string, password: string) {
  //   this.errorMessage = "";
  //   const user: IUser = {
  //     id: -1,
  //     username: name,
  //     password: password
  //   };

  //   if (this.validate(user)) {
  //     this.service.getAll()
  //       .subscribe(
  //         data => {
  //           const maxId = Math.max.apply(Math, data.map((o) => o.id));
  //           this.data = data.sort((a, b) => a.id < b.id ? -1 : 1);

  //           user.id = maxId + 1;
  //           this.service.add(user).subscribe(_ => {
  //             this.getAll();
  //           });
  //         },
  //         error => this.errorMessage = error
  //       );
  //   }
  // }

  getAll() {
    this.service.getAll()
      .subscribe(
        data => {
          console.log(data);
          this.data = data;
        },
        error => this.errorMessage = JSON.stringify(error)
      );
  }

  // update(id: string, name: string, password: string) {
  //   this.errorMessage = "";
  //   const user: IAuction = {
  //     id: parseInt(id),
  //     username: name,
  //     password: password
  //   };

  // }

  // delete(id: string) {
  //   this.service.delete(parseInt(id))
  //     .subscribe(
  //       _ => {
  //         this.getAll();
  //       },
  //       error => this.errorMessage = error);
  // }
}
