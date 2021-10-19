import { IBaseEntity } from "./base-entity.interface";

export interface IAuction extends IBaseEntity {
    user: string;
    categoryId: number;
    description: string;
    date: string;
}

