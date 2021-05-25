import { Component, OnInit } from '@angular/core';
import { News } from './news';

@Component({
  selector: 'app-root',
  templateUrl: './app.component.html',
  styleUrls: ['./app.component.css']
})
export class AppComponent implements OnInit {
  title = 'lab08';
  news: News[] = [];

  ngOnInit(): void {
    throw new Error('Method not implemented.');
  }

  
}
