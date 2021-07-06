import { IBaseEntity, IBaseEntities } from "./base-entity.interface";

export interface IUser extends IBaseEntity {
    name: string;
    birthday: string;
    address: string;
}

export interface IUsers extends IBaseEntities<IUser> {
    clients: IUser[];
}