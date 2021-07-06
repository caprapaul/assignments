import { Component, OnInit } from '@angular/core';
import { IUser } from 'src/app/models/user.interface';
import { UserService } from 'src/app/services/user.service';
import { ActivatedRoute } from '@angular/router';

@Component({
  selector: 'app-user',
  templateUrl: './user.component.html',
  styleUrls: ['./user.component.scss']
})
export class UserComponent implements OnInit {
  user: IUser | undefined

  constructor(private service: UserService, private route: ActivatedRoute) {
  }

  ngOnInit(): void {
    const routeParams = this.route.snapshot.paramMap;
    const id = Number(routeParams.get('id'));

    this.service.getOneWithPost(id).subscribe(
      data => {
        console.log(data);
        this.user = data;
      }
    );;
  }

}
