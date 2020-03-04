create table `user`
(
    `id` int unsigned not null auto_increment,
    `name` varchar(16) not null default '',
    `age` int unsigned not null default 0,
    `time` timestamp not null default current_timestamp,
    primary key (`id`),
    key `idx_name` (`name`),
    key `idx_time` (`time`)
) ENGINE=InnoaDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;

create table `fans`
(
    `id` int unsigned not null auto_increment,
    `uid` int unsigned not null default 0,
    `fid` int unsigned not null default 0,
    `time` timestamp not null default current_timestamp,
    primary key (`id`),
    key `idx_uid` (`uid`),
    key `idx_time` (`time`)
) ENGINE=InnoDB AUTO_INCREMENT=1 DEFAULT CHARSET=utf8;
