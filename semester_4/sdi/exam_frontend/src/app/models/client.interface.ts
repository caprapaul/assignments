import { IBaseEntity, IBaseEntities } from "./base-entity.interface";

export interface IClient extends IBaseEntity {
    name: string;
    isBusiness: boolean;
}

export interface IClients extends IBaseEntities<IClient> {
    clients: IClient[];
}