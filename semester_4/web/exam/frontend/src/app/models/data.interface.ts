import { IBaseEntity, IBaseEntities } from "./base-entity.interface";

export interface IUser extends IBaseEntity {
    username: string;
    password: string;
}

export interface IUsers extends IBaseEntities<IUser> {
    users: IUser[];
}