import { IBaseEntity, IBaseEntities } from "./base-entity.interface";

export interface IWebDomain extends IBaseEntity {
    name: string;
    price: number;
}

export interface IWebDomains extends IBaseEntities<IWebDomain> {
    webdomains: IWebDomain[];

}