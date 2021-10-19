import { IBaseEntity } from "./base-entity.interface";

export interface IFile extends IBaseEntity {
    userid: number;
    filename: string;
    filecontent: string;
    size: number;
    count: number;
}
