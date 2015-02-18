CREATE TABLE feed (
    id serial,
    url text NOT NULL
);

CREATE TABLE record (
    id serial,
    feed_id integer NOT NULL,
    hash character(32) NOT NULL,
    guid text,
    date bigint NOT NULL,
    link character varying(1024) DEFAULT NULL::character varying,
    title character varying(2048) DEFAULT NULL::character varying,
    description text,
    state smallint NOT NULL
);

CREATE FUNCTION add_record(feed_id integer, hash character, guid text, date bigint, link character varying, title character varying, description text) RETURNS void
    LANGUAGE plpgsql
    AS $$
BEGIN
LOOP
	UPDATE record
	SET guid = add_record.guid, date = add_record.date, link = add_record.link, title = add_record.title, description = add_record.description,
		state = CASE state
		WHEN 0 THEN 1
		ELSE state
		END
	WHERE record.feed_id=add_record.feed_id and record.hash=add_record.hash;
	
	IF found THEN
	    RETURN;
	END IF;
	
	BEGIN
		INSERT INTO record (feed_id, hash, guid,date,link,title,description, state)
		VALUES(feed_id, hash, guid,date,link,title,description, 0);
		RETURN;
	EXCEPTION WHEN unique_violation THEN
	END;
END LOOP;
END;
$$;

CREATE FUNCTION set_record_state(id integer, state smallint) RETURNS void
    LANGUAGE sql
    AS $$
	update record set state=set_record_state.state where id=set_record_state.id;
$$;

CREATE OR REPLACE FUNCTION get_records(
    feed_id integer,
    start_id integer,
    count integer,
    ref refcursor
    )
  RETURNS refcursor
  LANGUAGE plpgsql
  AS
$$
BEGIN
DECLARE
    BEGIN
	if start_id is null then
		OPEN ref FOR select id, record.feed_id, link, guid, date, link, title, description, state
		from record
		where record.feed_id=get_records.feed_id
		order by id desc
		limit count;
	else
		OPEN ref FOR select id, record.feed_id, link, guid, date, link, title, description, state
		from record
		where record.feed_id=get_records.feed_id and id < start_id
		order by id desc
		limit count;
	end if;
      RETURN ref;
    END;
END;
$$;
