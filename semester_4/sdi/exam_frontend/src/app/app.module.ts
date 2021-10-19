import { NgModule } from '@angular/core';
import { BrowserModule } from '@angular/platform-browser';

import { AppRoutingModule } from './app-routing.module';
import { AppComponent } from './app.component';
import { WebDomainsComponent } from './components/web-domains/web-domains.component';
import { ListComponent as WebDomainsListComponent } from './components/web-domains/list/list.component';
import { HttpClientModule } from '@angular/common/http';
import { ClientsComponent } from './components/clients/clients.component';
import { ListComponent } from './components/clients/list/list.component';

@NgModule({
  declarations: [
    AppComponent,
    WebDomainsComponent,
    WebDomainsListComponent,
    ClientsComponent,
    ListComponent
  ],
  imports: [
    BrowserModule,
    AppRoutingModule,
    HttpClientModule
  ],
  providers: [],
  bootstrap: [AppComponent]
})
export class AppModule { }
