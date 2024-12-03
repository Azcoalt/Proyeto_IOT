import {createPool} from 'mysql2/promise';

export const pool = createPool({
    host:"localhost",
    port: 3306,
    user:"root",
    password:"",
    database:"tinaco_iot",
    waitForConnections: true,
    connectionLimit: 10,
    maxIdle: 10, // max idle connections, the default value is the same as `connectionLimit`
    idleTimeout: 60000, // idle connections timeout, in milliseconds, the default value 60000
    queueLimit: 0,
    enableKeepAlive: true,
    keepAliveInitialDelay: 0,
});
