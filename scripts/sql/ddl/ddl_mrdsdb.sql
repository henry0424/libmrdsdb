create table configure.region_mgmt
(
    region varchar(256) not null
        constraint region_mgmt_pk
            primary key
);

alter table configure.region_mgmt owner to postgres;

create table configure.vendor_mgmt
(
    vendor varchar(256) not null
        constraint vendor_mgmt_pk
            primary key,
    vendor_vat varchar(256) not null,
    vendor_support text
);

alter table configure.vendor_mgmt owner to postgres;

create unique index vendor_mgmt_vendor_vat_uindex
    on configure.vendor_mgmt (vendor_vat);

create table class_reference.equipment_class
(
    equipment_class varchar(256) not null
        constraint equipment_class_mgmt_pk
            primary key
);

alter table class_reference.equipment_class owner to postgres;

create table configure.object_mgmt
(
    obj_uid varchar(256) not null
        constraint object_mgmt_pkey
            primary key,
    obj_id varchar(256) not null
        constraint object_mgmt_uk
            unique,
    enable boolean default true not null,
    create_ts timestamp default CURRENT_TIMESTAMP not null,
    update_ts timestamp default CURRENT_TIMESTAMP not null,
    region varchar(256) not null
        constraint object_mgmt_region_mgmt_region_fk
            references configure.region_mgmt
            on update cascade on delete cascade,
    equipment_class varchar(256) not null
        constraint object_mgmt_equipment_class_equipment_class_fk
            references class_reference.equipment_class
            on update cascade on delete cascade,
    vendor varchar(256) not null
        constraint object_mgmt_vendor_mgmt_vendor_fk
            references configure.vendor_mgmt
            on update cascade on delete cascade
);

alter table configure.object_mgmt owner to mrds_admin;

create table class_reference.carrier_class
(
    carrier_class varchar(256) not null
        constraint carrier_class_pk
            primary key
);

alter table class_reference.carrier_class owner to postgres;

create table configure.vehicle_mgmt
(
    vehicle_id varchar(256) not null
        constraint vehicle_mgmt_pk
            primary key
        constraint vehicle_mgmt_object_mgmt_obj_id_fk
            references configure.object_mgmt (obj_id)
            on update cascade on delete cascade,
    carrier_class varchar(256)
        constraint vehicle_mgmt_carrier_class_carrier_class_fk
            references class_reference.carrier_class
            on update cascade on delete cascade,
    slot_num integer not null,
    battery_threshold_full integer default 80 not null,
    battery_threshold_high integer default 50 not null,
    battery_threshold_low integer default 20 not null,
    macaddr macaddr,
    ipaddr cidr
);

alter table configure.vehicle_mgmt owner to mrds_admin;

create unique index vehicle_mgmt_mac_uindex
    on configure.vehicle_mgmt (macaddr);

create unique index vehicle_mgmt_ip_uindex
    on configure.vehicle_mgmt (ipaddr);

create table configure.equipment_mgmt
(
    equipment_id varchar(256) not null
        constraint equipment_mgmt_pk
            primary key
        constraint equipment_mgmt_object_mgmt_obj_id_fk
            references configure.object_mgmt (obj_id)
            on update cascade on delete cascade
);

alter table configure.equipment_mgmt owner to postgres;

create table messy.magic
(
    key varchar(256) not null
        constraint magic_pk
            primary key,
    value varchar(1024),
    update_ts timestamp default CURRENT_TIMESTAMP
);

alter table messy.magic owner to postgres;

create table messy.change_log
(
    "table" varchar(256),
    "user" varchar(256),
    change varchar(1000),
    update_ts timestamp default CURRENT_TIMESTAMP not null
);

alter table messy.change_log owner to postgres;

create table production.vehicle_status
(
    update_ts timestamp default CURRENT_TIMESTAMP not null,
    vehicle_id varchar(256) not null
        constraint vehilce_status_pk
            primary key
        constraint vehilce_status_vehicle_mgmt_vehicle_id_fk
            references configure.vehicle_mgmt
            on update cascade on delete cascade,
    vehicle_location varchar(256),
    vehicle_status varchar(256) default 'UNKNOW'::character varying not null,
    battery_status varchar(256) default 'UNKNOW'::character varying not null
);

alter table production.vehicle_status owner to postgres;

create table class_reference.event_class
(
    event_class varchar(256) not null
        constraint event_class_pk
            primary key
);

alter table class_reference.event_class owner to postgres;

create table production.event_log_vehicle
(
    msg_uuid varchar(256) not null,
    event_ts timestamp default CURRENT_TIMESTAMP not null,
    event_class varchar(256) not null
        constraint event_log_vehicle_event_class_event_class_fk
            references class_reference.event_class
            on update cascade on delete cascade,
    vehicle_id varchar(256) not null
        constraint event_log_vehicle_vehicle_mgmt_vehicle_id_fk
            references configure.vehicle_mgmt
            on update cascade on delete cascade,
    vehicle_status varchar(256) not null,
    vehicle_location varchar(256),
    carrier_id varchar(256),
    comment varchar(1000)
);

alter table production.event_log_vehicle owner to postgres;

create table production.transfer
(
    receive_ts timestamp default CURRENT_TIMESTAMP not null,
    command_id varchar(256) not null
        constraint transfer_pk
            primary key,
    source_port varchar(256),
    dest_port varchar(256) not null,
    priority integer default 1 not null,
    operator_id varchar(256) default 'MRDS_SYSTEM'::character varying not null,
    carrier_id varchar(256)
);

alter table production.transfer owner to postgres;

create table production.transfer_processing
(
    command_id varchar(256) not null
        constraint transfer_processing_transfer_command_id_fk
            references production.transfer
            on update cascade on delete cascade,
    merged_command_id varchar(256),
    vehicle_id varchar(256)
        constraint transfer_processing_vehicle_mgmt_vehicle_id_fk
            references configure.vehicle_mgmt
            on update cascade on delete cascade,
    transfer_state varchar(256) default 'QUEUE'::character varying not null,
    comment varchar(1000),
    magic varchar(1024)
);

alter table production.transfer_processing owner to postgres;

create table production.transfer_timestamp
(
    command_id varchar(256) not null
        constraint transfer_timestamp_transfer_command_id_fk
            references production.transfer
            on update cascade on delete cascade,
    update_ts timestamp default CURRENT_TIMESTAMP not null,
    merged_ts timestamp,
    assigned_ts timestamp,
    delivery_start_ts timestamp,
    delivery_stop_ts timestamp
);

alter table production.transfer_timestamp owner to postgres;

create table configure.parking_mgmt
(
    parking_space_id varchar(256) not null
        constraint parking_mgmt_pk
            primary key,
    parking_space_location varchar(256) not null,
    prefer_vehicle varchar(256) not null
);

alter table configure.parking_mgmt owner to postgres;

create unique index parking_mgmt_parking_space_location_uindex
    on configure.parking_mgmt (parking_space_location);

create table production.parking_status
(
    update_ts timestamp default CURRENT_TIMESTAMP not null,
    parking_space_id varchar(256) not null
        constraint parking_status_pk
            primary key
        constraint parking_status_parking_mgmt_parking_space_id_fk
            references configure.parking_mgmt
            on update cascade on delete cascade,
    booking varchar(256),
    booking_owner varchar(256),
    parking_vehicle_id varchar(256)
        constraint parking_status_vehicle_mgmt_vehicle_id_fk
            references configure.vehicle_mgmt
            on update cascade on delete cascade
);

alter table production.parking_status owner to postgres;

create unique index parking_status_parking_vehicle_id_uindex
    on production.parking_status (parking_vehicle_id);

create table configure.object_port_mgmt
(
    obj_id varchar(256) not null
        constraint object_port_mgmt_object_mgmt_obj_id_fk
            references configure.object_mgmt (obj_id)
            on update cascade on delete cascade,
    obj_port_id varchar(256) not null
        constraint object_port_mgmt_pk
            primary key
);

alter table configure.object_port_mgmt owner to postgres;

create table configure.dispatch_rule_mgmt
(
    source_port varchar(256) not null
        constraint dispatch_rule_mgmt_pk
            primary key
        constraint dispatch_rule_mgmt_object_port_mgmt_obj_port_id_fk
            references configure.object_port_mgmt
            on update cascade on delete cascade,
    prefer_vehicle varchar(256) not null
        constraint dispatch_rule_mgmt_vehicle_mgmt_vehicle_id_fk
            references configure.vehicle_mgmt
            on update cascade on delete cascade
);

alter table configure.dispatch_rule_mgmt owner to postgres;

create unique index object_port_mgmt_obj_port_id_uindex
    on configure.object_port_mgmt (obj_port_id);

create table production.object_port_status
(
    update_ts timestamp default CURRENT_TIMESTAMP not null,
    obj_id varchar(256) not null
        constraint object_port_status_object_mgmt_obj_id_fk
            references configure.object_mgmt (obj_id)
            on update cascade on delete cascade,
    obj_port_id varchar(256) not null
        constraint ect_port_status_pk
            primary key
        constraint object_port_status_object_port_mgmt_obj_port_id_fk
            references configure.object_port_mgmt
            on update cascade on delete cascade,
    carrier_id varchar(256)
);

alter table production.object_port_status owner to postgres;

create unique index ect_port_status_carrier_id_uindex
    on production.object_port_status (carrier_id);

create table production.universal_event_log
(
    event_ts timestamp default CURRENT_TIMESTAMP not null,
    event_class varchar not null
        constraint universal_event_log_event_class_event_class_fk
            references class_reference.event_class
            on update cascade on delete cascade,
    obj_class varchar(256) not null,
    obj_id varchar(256) not null,
    obj_port_id varchar(256)
        constraint universal_event_log_object_port_mgmt_obj_port_id_fk
            references configure.object_port_mgmt
            on update cascade on delete cascade,
    obj_location varchar(256),
    carrier_id varchar(256),
    comment varchar(1000),
    msg_uuid varchar(256)
);

alter table production.universal_event_log owner to postgres;

create unique index universal_event_log_msg_uuid_uindex
    on production.universal_event_log (msg_uuid);

create view production.transfer_view(receive_ts, command_id, source_port, dest_port, priority, operator_id, carrier_id, merged_command_id, vehicle_id, transfer_state, comment, update_ts, merged_ts, assigned_ts, delivery_start_ts, delivery_stop_ts) as
SELECT transfer.receive_ts,
       transfer.command_id,
       transfer.source_port,
       transfer.dest_port,
       transfer.priority,
       transfer.operator_id,
       transfer.carrier_id,
       transfer_processing.merged_command_id,
       transfer_processing.vehicle_id,
       transfer_processing.transfer_state,
       transfer_processing.comment,
       transfer_timestamp.update_ts,
       transfer_timestamp.merged_ts,
       transfer_timestamp.assigned_ts,
       transfer_timestamp.delivery_start_ts,
       transfer_timestamp.delivery_stop_ts
FROM production.transfer
         FULL JOIN production.transfer_processing ON transfer_processing.command_id::text = transfer.command_id::text
         FULL JOIN production.transfer_timestamp ON transfer_timestamp.command_id::text = transfer.command_id::text;

alter table production.transfer_view owner to postgres;

