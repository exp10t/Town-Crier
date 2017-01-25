// This file was generated by ODB, object-relational mapping (ORM)
// compiler for C++.
//

#include <odb/pre.hxx>

#include "transaction-record-odb.hxx"

#include <cassert>
#include <cstring>  // std::memcpy

#include <odb/schema-catalog-impl.hxx>

#include <odb/sqlite/traits.hxx>
#include <odb/sqlite/database.hxx>
#include <odb/sqlite/transaction.hxx>
#include <odb/sqlite/connection.hxx>
#include <odb/sqlite/statement.hxx>
#include <odb/sqlite/statement-cache.hxx>
#include <odb/sqlite/simple-object-statements.hxx>
#include <odb/sqlite/view-statements.hxx>
#include <odb/sqlite/container-statements.hxx>
#include <odb/sqlite/exceptions.hxx>
#include <odb/sqlite/simple-object-result.hxx>
#include <odb/sqlite/view-result.hxx>

namespace odb {
// TransactionRecord
//

struct access::object_traits_impl<::TransactionRecord, id_sqlite>::extra_statement_cache_type {
  extra_statement_cache_type(
      sqlite::connection &,
      image_type &,
      id_image_type &,
      sqlite::binding &,
      sqlite::binding &) {
  }
};

access::object_traits_impl<::TransactionRecord, id_sqlite>::id_type
access::object_traits_impl<::TransactionRecord, id_sqlite>::
id(const id_image_type &i) {
  sqlite::database *db(0);
  ODB_POTENTIALLY_UNUSED (db);

  id_type id;
  {
    sqlite::value_traits<
        long unsigned int,
        sqlite::id_integer>::set_value(
        id,
        i.id_value,
        i.id_null);
  }

  return id;
}

access::object_traits_impl<::TransactionRecord, id_sqlite>::id_type
access::object_traits_impl<::TransactionRecord, id_sqlite>::
id(const image_type &i) {
  sqlite::database *db(0);
  ODB_POTENTIALLY_UNUSED (db);

  id_type id;
  {
    sqlite::value_traits<
        long unsigned int,
        sqlite::id_integer>::set_value(
        id,
        i.__id_value,
        i.__id_null);
  }

  return id;
}

bool access::object_traits_impl<::TransactionRecord, id_sqlite>::
grow(image_type &i,
     bool *t) {
  ODB_POTENTIALLY_UNUSED (i);
  ODB_POTENTIALLY_UNUSED (t);

  bool grew(false);

  // __id
  //
  t[0UL] = false;

  // block_number
  //
  t[1UL] = false;

  // tx_hash
  //
  if (t[2UL]) {
    i.tx_hash_value.capacity(i.tx_hash_size);
    grew = true;
  }

  // request
  //
  if (t[3UL]) {
    i.request_value.capacity(i.request_size);
    grew = true;
  }

  // request_time
  //
  t[4UL] = false;

  // response
  //
  if (t[5UL]) {
    i.response_value.capacity(i.response_size);
    grew = true;
  }

  // response_time
  //
  t[6UL] = false;

  // n_retrial
  //
  t[7UL] = false;

  return grew;
}

void access::object_traits_impl<::TransactionRecord, id_sqlite>::
bind(sqlite::bind *b,
     image_type &i,
     sqlite::statement_kind sk) {
  ODB_POTENTIALLY_UNUSED (sk);

  using namespace sqlite;

  std::size_t n(0);

  // __id
  //
  if (sk != statement_update) {
    b[n].type = sqlite::bind::integer;
    b[n].buffer = &i.__id_value;
    b[n].is_null = &i.__id_null;
    n++;
  }

  // block_number
  //
  b[n].type = sqlite::bind::integer;
  b[n].buffer = &i.block_number_value;
  b[n].is_null = &i.block_number_null;
  n++;

  // tx_hash
  //
  b[n].type = sqlite::image_traits<
      ::std::string,
      sqlite::id_text>::bind_value;
  b[n].buffer = i.tx_hash_value.data();
  b[n].size = &i.tx_hash_size;
  b[n].capacity = i.tx_hash_value.capacity();
  b[n].is_null = &i.tx_hash_null;
  n++;

  // request
  //
  b[n].type = sqlite::image_traits<
      ::std::string,
      sqlite::id_text>::bind_value;
  b[n].buffer = i.request_value.data();
  b[n].size = &i.request_size;
  b[n].capacity = i.request_value.capacity();
  b[n].is_null = &i.request_null;
  n++;

  // request_time
  //
  b[n].type = sqlite::bind::integer;
  b[n].buffer = &i.request_time_value;
  b[n].is_null = &i.request_time_null;
  n++;

  // response
  //
  b[n].type = sqlite::image_traits<
      ::std::string,
      sqlite::id_text>::bind_value;
  b[n].buffer = i.response_value.data();
  b[n].size = &i.response_size;
  b[n].capacity = i.response_value.capacity();
  b[n].is_null = &i.response_null;
  n++;

  // response_time
  //
  b[n].type = sqlite::bind::integer;
  b[n].buffer = &i.response_time_value;
  b[n].is_null = &i.response_time_null;
  n++;

  // n_retrial
  //
  b[n].type = sqlite::bind::integer;
  b[n].buffer = &i.n_retrial_value;
  b[n].is_null = &i.n_retrial_null;
  n++;
}

void access::object_traits_impl<::TransactionRecord, id_sqlite>::
bind(sqlite::bind *b, id_image_type &i) {
  std::size_t n(0);
  b[n].type = sqlite::bind::integer;
  b[n].buffer = &i.id_value;
  b[n].is_null = &i.id_null;
}

bool access::object_traits_impl<::TransactionRecord, id_sqlite>::
init(image_type &i,
     const object_type &o,
     sqlite::statement_kind sk) {
  ODB_POTENTIALLY_UNUSED (i);
  ODB_POTENTIALLY_UNUSED (o);
  ODB_POTENTIALLY_UNUSED (sk);

  using namespace sqlite;

  bool grew(false);

  // __id
  //
  if (sk == statement_insert) {
    long unsigned int const &v =
        o.__id;

    bool is_null(false);
    sqlite::value_traits<
        long unsigned int,
        sqlite::id_integer>::set_image(
        i.__id_value,
        is_null,
        v);
    i.__id_null = is_null;
  }

  // block_number
  //
  {
    ::blocknum_t const &v =
        o.block_number;

    bool is_null(false);
    sqlite::value_traits<
        ::blocknum_t,
        sqlite::id_integer>::set_image(
        i.block_number_value,
        is_null,
        v);
    i.block_number_null = is_null;
  }

  // tx_hash
  //
  {
    ::std::string const &v =
        o.tx_hash;

    bool is_null(false);
    std::size_t cap(i.tx_hash_value.capacity());
    sqlite::value_traits<
        ::std::string,
        sqlite::id_text>::set_image(
        i.tx_hash_value,
        i.tx_hash_size,
        is_null,
        v);
    i.tx_hash_null = is_null;
    grew = grew || (cap != i.tx_hash_value.capacity());
  }

  // request
  //
  {
    ::std::string const &v =
        o.request;

    bool is_null(false);
    std::size_t cap(i.request_value.capacity());
    sqlite::value_traits<
        ::std::string,
        sqlite::id_text>::set_image(
        i.request_value,
        i.request_size,
        is_null,
        v);
    i.request_null = is_null;
    grew = grew || (cap != i.request_value.capacity());
  }

  // request_time
  //
  {
    ::time_t const &v =
        o.request_time;

    bool is_null(false);
    sqlite::value_traits<
        ::time_t,
        sqlite::id_integer>::set_image(
        i.request_time_value,
        is_null,
        v);
    i.request_time_null = is_null;
  }

  // response
  //
  {
    ::std::string const &v =
        o.response;

    bool is_null(false);
    std::size_t cap(i.response_value.capacity());
    sqlite::value_traits<
        ::std::string,
        sqlite::id_text>::set_image(
        i.response_value,
        i.response_size,
        is_null,
        v);
    i.response_null = is_null;
    grew = grew || (cap != i.response_value.capacity());
  }

  // response_time
  //
  {
    ::time_t const &v =
        o.response_time;

    bool is_null(false);
    sqlite::value_traits<
        ::time_t,
        sqlite::id_integer>::set_image(
        i.response_time_value,
        is_null,
        v);
    i.response_time_null = is_null;
  }

  // n_retrial
  //
  {
    unsigned int const &v =
        o.n_retrial;

    bool is_null(false);
    sqlite::value_traits<
        unsigned int,
        sqlite::id_integer>::set_image(
        i.n_retrial_value,
        is_null,
        v);
    i.n_retrial_null = is_null;
  }

  return grew;
}

void access::object_traits_impl<::TransactionRecord, id_sqlite>::
init(object_type &o,
     const image_type &i,
     database *db) {
  ODB_POTENTIALLY_UNUSED (o);
  ODB_POTENTIALLY_UNUSED (i);
  ODB_POTENTIALLY_UNUSED (db);

  // __id
  //
  {
    long unsigned int &v =
        o.__id;

    sqlite::value_traits<
        long unsigned int,
        sqlite::id_integer>::set_value(
        v,
        i.__id_value,
        i.__id_null);
  }

  // block_number
  //
  {
    ::blocknum_t &v =
        o.block_number;

    sqlite::value_traits<
        ::blocknum_t,
        sqlite::id_integer>::set_value(
        v,
        i.block_number_value,
        i.block_number_null);
  }

  // tx_hash
  //
  {
    ::std::string &v =
        o.tx_hash;

    sqlite::value_traits<
        ::std::string,
        sqlite::id_text>::set_value(
        v,
        i.tx_hash_value,
        i.tx_hash_size,
        i.tx_hash_null);
  }

  // request
  //
  {
    ::std::string &v =
        o.request;

    sqlite::value_traits<
        ::std::string,
        sqlite::id_text>::set_value(
        v,
        i.request_value,
        i.request_size,
        i.request_null);
  }

  // request_time
  //
  {
    ::time_t &v =
        o.request_time;

    sqlite::value_traits<
        ::time_t,
        sqlite::id_integer>::set_value(
        v,
        i.request_time_value,
        i.request_time_null);
  }

  // response
  //
  {
    ::std::string &v =
        o.response;

    sqlite::value_traits<
        ::std::string,
        sqlite::id_text>::set_value(
        v,
        i.response_value,
        i.response_size,
        i.response_null);
  }

  // response_time
  //
  {
    ::time_t &v =
        o.response_time;

    sqlite::value_traits<
        ::time_t,
        sqlite::id_integer>::set_value(
        v,
        i.response_time_value,
        i.response_time_null);
  }

  // n_retrial
  //
  {
    unsigned int &v =
        o.n_retrial;

    sqlite::value_traits<
        unsigned int,
        sqlite::id_integer>::set_value(
        v,
        i.n_retrial_value,
        i.n_retrial_null);
  }
}

void access::object_traits_impl<::TransactionRecord, id_sqlite>::
init(id_image_type &i, const id_type &id)
  {
    {
      bool is_null(false);
      sqlite::value_traits<
          long unsigned int,
          sqlite::id_integer>::set_image(
        i.id_value,
        is_null,
        id);
      i.id_null = is_null;
    }
  }

const char access::object_traits_impl<::TransactionRecord, id_sqlite>::persist_statement[] =
    "INSERT INTO \"TransactionRecord\" "
        "(\"id\", "
        "\"block_number\", "
        "\"tx_hash\", "
        "\"request\", "
        "\"request_time\", "
        "\"response\", "
        "\"response_time\", "
        "\"n_retrial\") "
        "VALUES "
        "(?, ?, ?, ?, ?, ?, ?, ?)";

const char access::object_traits_impl<::TransactionRecord, id_sqlite>::find_statement[] =
    "SELECT "
        "\"TransactionRecord\".\"id\", "
        "\"TransactionRecord\".\"block_number\", "
        "\"TransactionRecord\".\"tx_hash\", "
        "\"TransactionRecord\".\"request\", "
        "\"TransactionRecord\".\"request_time\", "
        "\"TransactionRecord\".\"response\", "
        "\"TransactionRecord\".\"response_time\", "
        "\"TransactionRecord\".\"n_retrial\" "
        "FROM \"TransactionRecord\" "
        "WHERE \"TransactionRecord\".\"id\"=?";

const char access::object_traits_impl<::TransactionRecord, id_sqlite>::update_statement[] =
    "UPDATE \"TransactionRecord\" "
        "SET "
        "\"block_number\"=?, "
        "\"tx_hash\"=?, "
        "\"request\"=?, "
        "\"request_time\"=?, "
        "\"response\"=?, "
        "\"response_time\"=?, "
        "\"n_retrial\"=? "
        "WHERE \"id\"=?";

const char access::object_traits_impl<::TransactionRecord, id_sqlite>::erase_statement[] =
    "DELETE FROM \"TransactionRecord\" "
        "WHERE \"id\"=?";

const char access::object_traits_impl<::TransactionRecord, id_sqlite>::query_statement[] =
    "SELECT "
        "\"TransactionRecord\".\"id\", "
        "\"TransactionRecord\".\"block_number\", "
        "\"TransactionRecord\".\"tx_hash\", "
        "\"TransactionRecord\".\"request\", "
        "\"TransactionRecord\".\"request_time\", "
        "\"TransactionRecord\".\"response\", "
        "\"TransactionRecord\".\"response_time\", "
        "\"TransactionRecord\".\"n_retrial\" "
        "FROM \"TransactionRecord\"";

const char access::object_traits_impl<::TransactionRecord, id_sqlite>::erase_query_statement[] =
    "DELETE FROM \"TransactionRecord\"";

const char access::object_traits_impl<::TransactionRecord, id_sqlite>::table_name[] =
    "\"TransactionRecord\"";

void access::object_traits_impl<::TransactionRecord, id_sqlite>::
persist(database &db, object_type &obj) {
  ODB_POTENTIALLY_UNUSED (db);

  using namespace sqlite;

  sqlite::connection &conn(
      sqlite::transaction::current().connection());
  statements_type &sts(
      conn.statement_cache().find_object<object_type>());

  callback(db,
           static_cast<const object_type &> (obj),
           callback_event::pre_persist);

  image_type &im(sts.image());
  binding &imb(sts.insert_image_binding());

  if (init(im, obj, statement_insert))
    im.version++;

  im.__id_null = true;

  if (im.version != sts.insert_image_version() ||
      imb.version == 0) {
    bind(imb.bind, im, statement_insert);
    sts.insert_image_version(im.version);
    imb.version++;
  }

  {
    id_image_type &i(sts.id_image());
    binding &b(sts.id_image_binding());
    if (i.version != sts.id_image_version() || b.version == 0) {
      bind(b.bind, i);
      sts.id_image_version(i.version);
      b.version++;
    }
  }

  insert_statement &st(sts.persist_statement());
  if (!st.execute())
    throw object_already_persistent();

  obj.__id = id(sts.id_image());

  callback(db,
           static_cast<const object_type &> (obj),
           callback_event::post_persist);
}

void access::object_traits_impl<::TransactionRecord, id_sqlite>::
update(database &db, const object_type &obj) {
  ODB_POTENTIALLY_UNUSED (db);

  using namespace sqlite;
  using sqlite::update_statement;

  callback(db, obj, callback_event::pre_update);

  sqlite::transaction &tr(sqlite::transaction::current());
  sqlite::connection &conn(tr.connection());
  statements_type &sts(
      conn.statement_cache().find_object<object_type>());

  const id_type &id(
      obj.__id);
  id_image_type &idi(sts.id_image());
  init(idi, id);

  image_type &im(sts.image());
  if (init(im, obj, statement_update))
    im.version++;

  bool u(false);
  binding &imb(sts.update_image_binding());
  if (im.version != sts.update_image_version() ||
      imb.version == 0) {
    bind(imb.bind, im, statement_update);
    sts.update_image_version(im.version);
    imb.version++;
    u = true;
  }

  binding &idb(sts.id_image_binding());
  if (idi.version != sts.update_id_image_version() ||
      idb.version == 0) {
    if (idi.version != sts.id_image_version() ||
        idb.version == 0) {
      bind(idb.bind, idi);
      sts.id_image_version(idi.version);
      idb.version++;
    }

    sts.update_id_image_version(idi.version);

    if (!u)
      imb.version++;
  }

  update_statement &st(sts.update_statement());
  if (st.execute() == 0)
    throw object_not_persistent();

  callback(db, obj, callback_event::post_update);
  pointer_cache_traits::update(db, obj);
}

void access::object_traits_impl<::TransactionRecord, id_sqlite>::
erase(database &db, const id_type &id) {
  using namespace sqlite;

  ODB_POTENTIALLY_UNUSED (db);

  sqlite::connection &conn(
      sqlite::transaction::current().connection());
  statements_type &sts(
      conn.statement_cache().find_object<object_type>());

  id_image_type &i(sts.id_image());
  init(i, id);

  binding &idb(sts.id_image_binding());
  if (i.version != sts.id_image_version() || idb.version == 0) {
    bind(idb.bind, i);
    sts.id_image_version(i.version);
    idb.version++;
  }

  if (sts.erase_statement().execute() != 1)
    throw object_not_persistent();

  pointer_cache_traits::erase(db, id);
}

access::object_traits_impl<::TransactionRecord, id_sqlite>::pointer_type
access::object_traits_impl<::TransactionRecord, id_sqlite>::
find(database &db, const id_type &id) {
  using namespace sqlite;

  {
    pointer_type p(pointer_cache_traits::find(db, id));

    if (!pointer_traits::null_ptr(p))
      return p;
  }

  sqlite::connection &conn(
      sqlite::transaction::current().connection());
  statements_type &sts(
      conn.statement_cache().find_object<object_type>());

  statements_type::auto_lock l(sts);

  if (l.locked()) {
    if (!find_(sts, &id))
      return pointer_type();
  }

  pointer_type p(
      access::object_factory<object_type, pointer_type>::create ());
  pointer_traits::guard pg(p);

  pointer_cache_traits::insert_guard ig(
      pointer_cache_traits::insert(db, id, p));

  object_type &obj(pointer_traits::get_ref(p));

  if (l.locked()) {
    select_statement &st(sts.find_statement());
    ODB_POTENTIALLY_UNUSED (st);

    callback(db, obj, callback_event::pre_load);
    init(obj, sts.image(), &db);
    load_(sts, obj, false);
    sts.load_delayed(0);
    l.unlock();
    callback(db, obj, callback_event::post_load);
    pointer_cache_traits::load(ig.position());
  } else
    sts.delay_load(id, obj, ig.position());

  ig.release();
  pg.release();
  return p;
}

bool access::object_traits_impl<::TransactionRecord, id_sqlite>::
find(database &db, const id_type &id, object_type &obj) {
  using namespace sqlite;

  sqlite::connection &conn(
      sqlite::transaction::current().connection());
  statements_type &sts(
      conn.statement_cache().find_object<object_type>());

  statements_type::auto_lock l(sts);

  if (!find_(sts, &id))
    return false;

  select_statement &st(sts.find_statement());
  ODB_POTENTIALLY_UNUSED (st);

  reference_cache_traits::position_type pos(
      reference_cache_traits::insert(db, id, obj));
  reference_cache_traits::insert_guard ig(pos);

  callback(db, obj, callback_event::pre_load);
  init(obj, sts.image(), &db);
  load_(sts, obj, false);
  sts.load_delayed(0);
  l.unlock();
  callback(db, obj, callback_event::post_load);
  reference_cache_traits::load(pos);
  ig.release();
  return true;
}

bool access::object_traits_impl<::TransactionRecord, id_sqlite>::
reload(database &db, object_type &obj) {
  using namespace sqlite;

  sqlite::connection &conn(
      sqlite::transaction::current().connection());
  statements_type &sts(
      conn.statement_cache().find_object<object_type>());

  statements_type::auto_lock l(sts);

  const id_type &id(
      obj.__id);

  if (!find_(sts, &id))
    return false;

  select_statement &st(sts.find_statement());
  ODB_POTENTIALLY_UNUSED (st);

  callback(db, obj, callback_event::pre_load);
  init(obj, sts.image(), &db);
  load_(sts, obj, true);
  sts.load_delayed(0);
  l.unlock();
  callback(db, obj, callback_event::post_load);
  return true;
}

bool access::object_traits_impl<::TransactionRecord, id_sqlite>::
find_(statements_type &sts,
      const id_type *id) {
  using namespace sqlite;

  id_image_type &i(sts.id_image());
  init(i, *id);

  binding &idb(sts.id_image_binding());
  if (i.version != sts.id_image_version() || idb.version == 0) {
    bind(idb.bind, i);
    sts.id_image_version(i.version);
    idb.version++;
  }

  image_type &im(sts.image());
  binding &imb(sts.select_image_binding());

  if (im.version != sts.select_image_version() ||
      imb.version == 0) {
    bind(imb.bind, im, statement_select);
    sts.select_image_version(im.version);
    imb.version++;
  }

  select_statement &st(sts.find_statement());

  st.execute();
  auto_result ar(st);
  select_statement::result r(st.fetch());

  if (r == select_statement::truncated) {
    if (grow(im, sts.select_image_truncated()))
      im.version++;

    if (im.version != sts.select_image_version()) {
      bind(imb.bind, im, statement_select);
      sts.select_image_version(im.version);
      imb.version++;
      st.refetch();
    }
  }

  return r != select_statement::no_data;
}

result<access::object_traits_impl<::TransactionRecord, id_sqlite>::object_type>
access::object_traits_impl<::TransactionRecord, id_sqlite>::
query(database &, const query_base_type &q) {
  using namespace sqlite;
  using odb::details::shared;
  using odb::details::shared_ptr;

  sqlite::connection &conn(
      sqlite::transaction::current().connection());

  statements_type &sts(
      conn.statement_cache().find_object<object_type>());

  image_type &im(sts.image());
  binding &imb(sts.select_image_binding());

  if (im.version != sts.select_image_version() ||
      imb.version == 0) {
    bind(imb.bind, im, statement_select);
    sts.select_image_version(im.version);
    imb.version++;
  }

  std::string text(query_statement);
  if (!q.empty()) {
    text += " ";
    text += q.clause();
  }

  q.init_parameters();
  shared_ptr<select_statement> st(
      new(shared) select_statement(
          conn,
          text,
          false,
          true,
          q.parameters_binding(),
          imb));

  st->execute();

  shared_ptr<odb::object_result_impl<object_type> > r(
      new(shared) sqlite::object_result_impl<object_type>(
          q, st, sts, 0));

  return result<object_type>(r);
}

unsigned long long access::object_traits_impl<::TransactionRecord, id_sqlite>::
erase_query(database &, const query_base_type &q) {
  using namespace sqlite;

  sqlite::connection &conn(
      sqlite::transaction::current().connection());

  std::string text(erase_query_statement);
  if (!q.empty()) {
    text += ' ';
    text += q.clause();
  }

  q.init_parameters();
  delete_statement st(
      conn,
      text,
      q.parameters_binding());

  return st.execute();
}

// TransactionStat
//

bool access::view_traits_impl<::TransactionStat, id_sqlite>::
grow(image_type &i,
     bool *t) {
  ODB_POTENTIALLY_UNUSED (i);
  ODB_POTENTIALLY_UNUSED (t);

  bool grew(false);

  // count
  //
  t[0UL] = false;

  // lastBlock
  //
  t[1UL] = false;

  return grew;
}

void access::view_traits_impl<::TransactionStat, id_sqlite>::
bind(sqlite::bind *b,
     image_type &i) {
  using namespace sqlite;

  sqlite::statement_kind sk(statement_select);
  ODB_POTENTIALLY_UNUSED (sk);

  std::size_t n(0);

  // count
  //
  b[n].type = sqlite::bind::integer;
  b[n].buffer = &i.count_value;
  b[n].is_null = &i.count_null;
  n++;

  // lastBlock
  //
  b[n].type = sqlite::bind::integer;
  b[n].buffer = &i.lastBlock_value;
  b[n].is_null = &i.lastBlock_null;
  n++;
}

void access::view_traits_impl<::TransactionStat, id_sqlite>::
init(view_type &o,
     const image_type &i,
     database *db) {
  ODB_POTENTIALLY_UNUSED (o);
  ODB_POTENTIALLY_UNUSED (i);
  ODB_POTENTIALLY_UNUSED (db);

  // count
  //
  {
    ::std::size_t &v =
        o.count;

    sqlite::value_traits<
        ::std::size_t,
        sqlite::id_integer>::set_value(
        v,
        i.count_value,
        i.count_null);
  }

  // lastBlock
  //
  {
    ::blocknum_t &v =
        o.lastBlock;

    sqlite::value_traits<
        ::blocknum_t,
        sqlite::id_integer>::set_value(
        v,
        i.lastBlock_value,
        i.lastBlock_null);
  }
}

access::view_traits_impl<::TransactionStat, id_sqlite>::query_base_type
access::view_traits_impl<::TransactionStat, id_sqlite>::
query_statement(const query_base_type &q) {
  query_base_type r(
      "SELECT "
          "count(\"TransactionRecord\".\"id\"), "
          "max(\"TransactionRecord\".\"block_number\") ");

  r += "FROM \"TransactionRecord\"";

  if (!q.empty()) {
    r += " ";
    r += q.clause_prefix();
    r += q;
  }

  return r;
}

result<access::view_traits_impl<::TransactionStat, id_sqlite>::view_type>
access::view_traits_impl<::TransactionStat, id_sqlite>::
query(database &, const query_base_type &q) {
  using namespace sqlite;
  using odb::details::shared;
  using odb::details::shared_ptr;

  sqlite::connection &conn(
      sqlite::transaction::current().connection());
  statements_type &sts(
      conn.statement_cache().find_view<view_type>());

  image_type &im(sts.image());
  binding &imb(sts.image_binding());

  if (im.version != sts.image_version() || imb.version == 0) {
    bind(imb.bind, im);
    sts.image_version(im.version);
    imb.version++;
  }

  const query_base_type &qs(query_statement(q));
  qs.init_parameters();
  shared_ptr<select_statement> st(
      new(shared) select_statement(
          conn,
          qs.clause(),
          false,
          true,
          qs.parameters_binding(),
          imb));

  st->execute();

  shared_ptr<odb::view_result_impl<view_type> > r(
      new(shared) sqlite::view_result_impl<view_type>(
          qs, st, sts, 0));

  return result<view_type>(r);
}
}

namespace odb {
static bool
create_schema(database &db, unsigned short pass, bool drop) {
  ODB_POTENTIALLY_UNUSED (db);
  ODB_POTENTIALLY_UNUSED (pass);
  ODB_POTENTIALLY_UNUSED (drop);

  if (drop) {
    switch (pass) {
      case 1: {
        return true;
      }
      case 2: {
        db.execute("DROP TABLE IF EXISTS \"TransactionRecord\"");
        return false;
      }
      }
    } else {
    switch (pass) {
      case 1: {
        db.execute("CREATE TABLE \"TransactionRecord\" (\n"
                       "  \"id\" INTEGER NOT NULL PRIMARY KEY AUTOINCREMENT,\n"
                       "  \"block_number\" INTEGER NOT NULL,\n"
                       "  \"tx_hash\" TEXT NOT NULL,\n"
                       "  \"request\" TEXT NOT NULL,\n"
                       "  \"request_time\" INTEGER NOT NULL,\n"
                       "  \"response\" TEXT NOT NULL,\n"
                       "  \"response_time\" INTEGER NOT NULL,\n"
                       "  \"n_retrial\" INTEGER NOT NULL)");
        db.execute("CREATE UNIQUE INDEX \"TransactionRecord_tx_hash_i\"\n"
                       "  ON \"TransactionRecord\" (\"tx_hash\")");
        return false;
      }
    }
  }

  return false;
}

static const schema_catalog_create_entry
    create_schema_entry_(
    id_sqlite,
    "",
    &create_schema);
}

#include <odb/post.hxx>
