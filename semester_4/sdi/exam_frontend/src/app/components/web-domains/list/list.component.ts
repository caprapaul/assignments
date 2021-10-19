import { Component, OnInit } from '@angular/core';
import { IWebDomain } from 'src/app/models/web-domain.interface';
import { WebDomainService } from 'src/app/services/web-domain.service';

@Component({
  selector: 'web-domains-list',
  templateUrl: './list.component.html',
  styleUrls: ['./list.component.scss'],
})
export class ListComponent implements OnInit {
  webDomains: IWebDomain[];
  errorMessage: string;

  constructor(private service: WebDomainService) {
    this.webDomains = [];
    this.errorMessage = "";
  }

  ngOnInit(): void {
    this.getAll();
  }

  validate(domain: IWebDomain) {
    if (domain.name.length < 3) {
      this.errorMessage = "Name is too short";

      return false;
    }

    if (!domain.name.includes(".")) {
      this.errorMessage = "Invalid name";

      return false;
    }

    if (isNaN(domain.price) || domain.price == null) {
      this.errorMessage = "Invalid price";

      return false;
    }

    return true;
  }

  add(name: string, price: string) {
    this.errorMessage = "";
    const domain: IWebDomain = {
      id: -1,
      name: name,
      price: parseInt(price)
    };

    if (this.validate(domain)) {
      this.service.getAll()
        .subscribe(
          data => {
            const maxId = Math.max.apply(Math, data.webdomains.map((o) => o.id));
            this.webDomains = data.webdomains.sort((a, b) => a.id < b.id ? -1 : 1);

            domain.id = maxId + 1;
            this.service.add(domain).subscribe(_ => {
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
          this.webDomains = data.webdomains.sort((a, b) => a.id < b.id ? -1 : 1);
        },
        error => this.errorMessage = error
      );
  }

  update(id: string, name: string, price: string) {
    this.errorMessage = "";
    const domain: IWebDomain = {
      id: parseInt(id),
      name: name,
      price: parseInt(price)
    };

    if (this.validate(domain)) {
      this.service.update(domain)
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

    this.service.filter(value)
      .subscribe(
        data => {
          this.webDomains = data.webdomains.sort((a, b) => a.id - b.id);
        },
        error => this.errorMessage = error
      );
  }
}
