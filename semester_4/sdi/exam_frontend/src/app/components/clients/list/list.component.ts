import { Component, OnInit } from '@angular/core';
import { IClient, IClients } from 'src/app/models/client.interface';
import { ClientService } from 'src/app/services/client.service';

@Component({
  selector: 'clients-list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.scss']
})
export class ListComponent implements OnInit {
  clients: IClient[];
  errorMessage: string;

  constructor(private service: ClientService) {
    this.clients = [];
    this.errorMessage = "";
  }

  ngOnInit(): void {
    this.getAll();
  }

  validate(client: IClient) {
    if (client.name.length < 3) {
      this.errorMessage = "Name too short";

      return false;
    }

    return true;
  }

  add(name: string, isBusiness: boolean) {
    this.errorMessage = "";
    const client: IClient = {
      id: -1,
      name: name,
      isBusiness: isBusiness
    };

    if (this.validate(client)) {
      this.service.getAll()
        .subscribe(
          data => {
            const maxId = Math.max.apply(Math, data.clients.map((o) => o.id));
            this.clients = data.clients.sort((a, b) => a.id < b.id ? -1 : 1);

            client.id = maxId + 1;
            this.service.add(client).subscribe(_ => {
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
          this.clients = data.clients.sort((a, b) => a.id < b.id ? -1 : 1);
        },
        error => this.errorMessage = error
      );
  }

  update(id: string, name: string, isBusiness: boolean) {
    this.errorMessage = "";
    const client: IClient = {
      id: parseInt(id),
      name: name,
      isBusiness: isBusiness
    };

    if (this.validate(client)) {
      this.service.update(client)
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
    if (!value) {
      this.getAll();

      return;
    }

    this.service.getAll()
      .subscribe(
        data => {
          this.clients = data.clients
            .filter(client => client.name.toUpperCase().includes(value.toUpperCase()))
            .sort((a, b) => a.id - b.id);
        },
        error => this.errorMessage = error
      );
  }
}
