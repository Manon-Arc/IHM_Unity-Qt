CREATE TABLE sqlite_sequence(name,seq);
CREATE TABLE IF NOT EXISTS "users"
(
    Id       integer not null
        constraint users_pk
            primary key autoincrement,
    username TEXT    not null,
    password TEXT    not null
, firstname integer, name integer);
CREATE TABLE projects
(
    Id   integer not null
        constraint projects_pk
            primary key autoincrement,
    name text    not null
);
CREATE TABLE user_project
(
    Id      integer not null
        constraint user_project_pk
            primary key,
    user    integer not null
        constraint user_project_users_Id_fk
            references users,
    project integer not null
        constraint user_project_projects_Id_fk
            references projects
);
