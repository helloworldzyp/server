// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: msg.proto

#include "msg.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
extern PROTOBUF_INTERNAL_EXPORT_msg_2eproto ::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_MyMsgHead_msg_2eproto;
class MyMsgHeadDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<MyMsgHead> _instance;
} _MyMsgHead_default_instance_;
class MyLoginMsgDefaultTypeInternal {
 public:
  ::PROTOBUF_NAMESPACE_ID::internal::ExplicitlyConstructed<MyLoginMsg> _instance;
} _MyLoginMsg_default_instance_;
static void InitDefaultsscc_info_MyLoginMsg_msg_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_MyLoginMsg_default_instance_;
    new (ptr) ::MyLoginMsg();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::MyLoginMsg::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<1> scc_info_MyLoginMsg_msg_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 1, 0, InitDefaultsscc_info_MyLoginMsg_msg_2eproto}, {
      &scc_info_MyMsgHead_msg_2eproto.base,}};

static void InitDefaultsscc_info_MyMsgHead_msg_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::_MyMsgHead_default_instance_;
    new (ptr) ::MyMsgHead();
    ::PROTOBUF_NAMESPACE_ID::internal::OnShutdownDestroyMessage(ptr);
  }
  ::MyMsgHead::InitAsDefaultInstance();
}

::PROTOBUF_NAMESPACE_ID::internal::SCCInfo<0> scc_info_MyMsgHead_msg_2eproto =
    {{ATOMIC_VAR_INIT(::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase::kUninitialized), 0, 0, InitDefaultsscc_info_MyMsgHead_msg_2eproto}, {}};

static ::PROTOBUF_NAMESPACE_ID::Metadata file_level_metadata_msg_2eproto[2];
static constexpr ::PROTOBUF_NAMESPACE_ID::EnumDescriptor const** file_level_enum_descriptors_msg_2eproto = nullptr;
static constexpr ::PROTOBUF_NAMESPACE_ID::ServiceDescriptor const** file_level_service_descriptors_msg_2eproto = nullptr;

const ::PROTOBUF_NAMESPACE_ID::uint32 TableStruct_msg_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::MyMsgHead, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::MyMsgHead, cmd_),
  PROTOBUF_FIELD_OFFSET(::MyMsgHead, datalen_),
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::MyLoginMsg, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::MyLoginMsg, head_),
  PROTOBUF_FIELD_OFFSET(::MyLoginMsg, name_),
  PROTOBUF_FIELD_OFFSET(::MyLoginMsg, age_),
};
static const ::PROTOBUF_NAMESPACE_ID::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::MyMsgHead)},
  { 7, -1, sizeof(::MyLoginMsg)},
};

static ::PROTOBUF_NAMESPACE_ID::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_MyMsgHead_default_instance_),
  reinterpret_cast<const ::PROTOBUF_NAMESPACE_ID::Message*>(&::_MyLoginMsg_default_instance_),
};

const char descriptor_table_protodef_msg_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\tmsg.proto\")\n\tMyMsgHead\022\013\n\003cmd\030\001 \001(\005\022\017\n"
  "\007dataLen\030\002 \001(\005\"A\n\nMyLoginMsg\022\030\n\004head\030\001 \001"
  "(\0132\n.MyMsgHead\022\014\n\004name\030\002 \001(\t\022\013\n\003age\030\003 \001("
  "\005b\006proto3"
  ;
static const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable*const descriptor_table_msg_2eproto_deps[1] = {
};
static ::PROTOBUF_NAMESPACE_ID::internal::SCCInfoBase*const descriptor_table_msg_2eproto_sccs[2] = {
  &scc_info_MyLoginMsg_msg_2eproto.base,
  &scc_info_MyMsgHead_msg_2eproto.base,
};
static ::PROTOBUF_NAMESPACE_ID::internal::once_flag descriptor_table_msg_2eproto_once;
const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_msg_2eproto = {
  false, false, descriptor_table_protodef_msg_2eproto, "msg.proto", 129,
  &descriptor_table_msg_2eproto_once, descriptor_table_msg_2eproto_sccs, descriptor_table_msg_2eproto_deps, 2, 0,
  schemas, file_default_instances, TableStruct_msg_2eproto::offsets,
  file_level_metadata_msg_2eproto, 2, file_level_enum_descriptors_msg_2eproto, file_level_service_descriptors_msg_2eproto,
};

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_msg_2eproto = (static_cast<void>(::PROTOBUF_NAMESPACE_ID::internal::AddDescriptors(&descriptor_table_msg_2eproto)), true);

// ===================================================================

void MyMsgHead::InitAsDefaultInstance() {
}
class MyMsgHead::_Internal {
 public:
};

MyMsgHead::MyMsgHead(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:MyMsgHead)
}
MyMsgHead::MyMsgHead(const MyMsgHead& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&cmd_, &from.cmd_,
    static_cast<size_t>(reinterpret_cast<char*>(&datalen_) -
    reinterpret_cast<char*>(&cmd_)) + sizeof(datalen_));
  // @@protoc_insertion_point(copy_constructor:MyMsgHead)
}

void MyMsgHead::SharedCtor() {
  ::memset(&cmd_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&datalen_) -
      reinterpret_cast<char*>(&cmd_)) + sizeof(datalen_));
}

MyMsgHead::~MyMsgHead() {
  // @@protoc_insertion_point(destructor:MyMsgHead)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void MyMsgHead::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
}

void MyMsgHead::ArenaDtor(void* object) {
  MyMsgHead* _this = reinterpret_cast< MyMsgHead* >(object);
  (void)_this;
}
void MyMsgHead::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void MyMsgHead::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const MyMsgHead& MyMsgHead::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_MyMsgHead_msg_2eproto.base);
  return *internal_default_instance();
}


void MyMsgHead::Clear() {
// @@protoc_insertion_point(message_clear_start:MyMsgHead)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&cmd_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&datalen_) -
      reinterpret_cast<char*>(&cmd_)) + sizeof(datalen_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* MyMsgHead::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // int32 cmd = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 8)) {
          cmd_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int32 dataLen = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 16)) {
          datalen_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* MyMsgHead::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:MyMsgHead)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 cmd = 1;
  if (this->cmd() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(1, this->_internal_cmd(), target);
  }

  // int32 dataLen = 2;
  if (this->datalen() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(2, this->_internal_datalen(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:MyMsgHead)
  return target;
}

size_t MyMsgHead::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:MyMsgHead)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 cmd = 1;
  if (this->cmd() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_cmd());
  }

  // int32 dataLen = 2;
  if (this->datalen() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_datalen());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void MyMsgHead::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:MyMsgHead)
  GOOGLE_DCHECK_NE(&from, this);
  const MyMsgHead* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<MyMsgHead>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:MyMsgHead)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:MyMsgHead)
    MergeFrom(*source);
  }
}

void MyMsgHead::MergeFrom(const MyMsgHead& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:MyMsgHead)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.cmd() != 0) {
    _internal_set_cmd(from._internal_cmd());
  }
  if (from.datalen() != 0) {
    _internal_set_datalen(from._internal_datalen());
  }
}

void MyMsgHead::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:MyMsgHead)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MyMsgHead::CopyFrom(const MyMsgHead& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:MyMsgHead)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MyMsgHead::IsInitialized() const {
  return true;
}

void MyMsgHead::InternalSwap(MyMsgHead* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(MyMsgHead, datalen_)
      + sizeof(MyMsgHead::datalen_)
      - PROTOBUF_FIELD_OFFSET(MyMsgHead, cmd_)>(
          reinterpret_cast<char*>(&cmd_),
          reinterpret_cast<char*>(&other->cmd_));
}

::PROTOBUF_NAMESPACE_ID::Metadata MyMsgHead::GetMetadata() const {
  return GetMetadataStatic();
}


// ===================================================================

void MyLoginMsg::InitAsDefaultInstance() {
  ::_MyLoginMsg_default_instance_._instance.get_mutable()->head_ = const_cast< ::MyMsgHead*>(
      ::MyMsgHead::internal_default_instance());
}
class MyLoginMsg::_Internal {
 public:
  static const ::MyMsgHead& head(const MyLoginMsg* msg);
};

const ::MyMsgHead&
MyLoginMsg::_Internal::head(const MyLoginMsg* msg) {
  return *msg->head_;
}
MyLoginMsg::MyLoginMsg(::PROTOBUF_NAMESPACE_ID::Arena* arena)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena) {
  SharedCtor();
  RegisterArenaDtor(arena);
  // @@protoc_insertion_point(arena_constructor:MyLoginMsg)
}
MyLoginMsg::MyLoginMsg(const MyLoginMsg& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (!from._internal_name().empty()) {
    name_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), from._internal_name(),
      GetArena());
  }
  if (from._internal_has_head()) {
    head_ = new ::MyMsgHead(*from.head_);
  } else {
    head_ = nullptr;
  }
  age_ = from.age_;
  // @@protoc_insertion_point(copy_constructor:MyLoginMsg)
}

void MyLoginMsg::SharedCtor() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&scc_info_MyLoginMsg_msg_2eproto.base);
  name_.UnsafeSetDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  ::memset(&head_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&age_) -
      reinterpret_cast<char*>(&head_)) + sizeof(age_));
}

MyLoginMsg::~MyLoginMsg() {
  // @@protoc_insertion_point(destructor:MyLoginMsg)
  SharedDtor();
  _internal_metadata_.Delete<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

void MyLoginMsg::SharedDtor() {
  GOOGLE_DCHECK(GetArena() == nullptr);
  name_.DestroyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
  if (this != internal_default_instance()) delete head_;
}

void MyLoginMsg::ArenaDtor(void* object) {
  MyLoginMsg* _this = reinterpret_cast< MyLoginMsg* >(object);
  (void)_this;
}
void MyLoginMsg::RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena*) {
}
void MyLoginMsg::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const MyLoginMsg& MyLoginMsg::default_instance() {
  ::PROTOBUF_NAMESPACE_ID::internal::InitSCC(&::scc_info_MyLoginMsg_msg_2eproto.base);
  return *internal_default_instance();
}


void MyLoginMsg::Clear() {
// @@protoc_insertion_point(message_clear_start:MyLoginMsg)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  name_.ClearToEmpty(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  if (GetArena() == nullptr && head_ != nullptr) {
    delete head_;
  }
  head_ = nullptr;
  age_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* MyLoginMsg::_InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  ::PROTOBUF_NAMESPACE_ID::Arena* arena = GetArena(); (void)arena;
  while (!ctx->Done(&ptr)) {
    ::PROTOBUF_NAMESPACE_ID::uint32 tag;
    ptr = ::PROTOBUF_NAMESPACE_ID::internal::ReadTag(ptr, &tag);
    CHK_(ptr);
    switch (tag >> 3) {
      // .MyMsgHead head = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 10)) {
          ptr = ctx->ParseMessage(_internal_mutable_head(), ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // string name = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 18)) {
          auto str = _internal_mutable_name();
          ptr = ::PROTOBUF_NAMESPACE_ID::internal::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(::PROTOBUF_NAMESPACE_ID::internal::VerifyUTF8(str, "MyLoginMsg.name"));
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      // int32 age = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<::PROTOBUF_NAMESPACE_ID::uint8>(tag) == 24)) {
          age_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else goto handle_unusual;
        continue;
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->SetLastTag(tag);
          goto success;
        }
        ptr = UnknownFieldParse(tag,
            _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
            ptr, ctx);
        CHK_(ptr != nullptr);
        continue;
      }
    }  // switch
  }  // while
success:
  return ptr;
failure:
  ptr = nullptr;
  goto success;
#undef CHK_
}

::PROTOBUF_NAMESPACE_ID::uint8* MyLoginMsg::_InternalSerialize(
    ::PROTOBUF_NAMESPACE_ID::uint8* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:MyLoginMsg)
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // .MyMsgHead head = 1;
  if (this->has_head()) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::
      InternalWriteMessage(
        1, _Internal::head(this), target, stream);
  }

  // string name = 2;
  if (this->name().size() > 0) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_name().data(), static_cast<int>(this->_internal_name().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "MyLoginMsg.name");
    target = stream->WriteStringMaybeAliased(
        2, this->_internal_name(), target);
  }

  // int32 age = 3;
  if (this->age() != 0) {
    target = stream->EnsureSpace(target);
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::WriteInt32ToArray(3, this->_internal_age(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::PROTOBUF_NAMESPACE_ID::internal::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:MyLoginMsg)
  return target;
}

size_t MyLoginMsg::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:MyLoginMsg)
  size_t total_size = 0;

  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string name = 2;
  if (this->name().size() > 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_name());
  }

  // .MyMsgHead head = 1;
  if (this->has_head()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::MessageSize(
        *head_);
  }

  // int32 age = 3;
  if (this->age() != 0) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::Int32Size(
        this->_internal_age());
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    return ::PROTOBUF_NAMESPACE_ID::internal::ComputeUnknownFieldsSize(
        _internal_metadata_, total_size, &_cached_size_);
  }
  int cached_size = ::PROTOBUF_NAMESPACE_ID::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void MyLoginMsg::MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:MyLoginMsg)
  GOOGLE_DCHECK_NE(&from, this);
  const MyLoginMsg* source =
      ::PROTOBUF_NAMESPACE_ID::DynamicCastToGenerated<MyLoginMsg>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:MyLoginMsg)
    ::PROTOBUF_NAMESPACE_ID::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:MyLoginMsg)
    MergeFrom(*source);
  }
}

void MyLoginMsg::MergeFrom(const MyLoginMsg& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:MyLoginMsg)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  if (from.name().size() > 0) {
    _internal_set_name(from._internal_name());
  }
  if (from.has_head()) {
    _internal_mutable_head()->::MyMsgHead::MergeFrom(from._internal_head());
  }
  if (from.age() != 0) {
    _internal_set_age(from._internal_age());
  }
}

void MyLoginMsg::CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:MyLoginMsg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void MyLoginMsg::CopyFrom(const MyLoginMsg& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:MyLoginMsg)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool MyLoginMsg::IsInitialized() const {
  return true;
}

void MyLoginMsg::InternalSwap(MyLoginMsg* other) {
  using std::swap;
  _internal_metadata_.Swap<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(&other->_internal_metadata_);
  name_.Swap(&other->name_, &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArena());
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(MyLoginMsg, age_)
      + sizeof(MyLoginMsg::age_)
      - PROTOBUF_FIELD_OFFSET(MyLoginMsg, head_)>(
          reinterpret_cast<char*>(&head_),
          reinterpret_cast<char*>(&other->head_));
}

::PROTOBUF_NAMESPACE_ID::Metadata MyLoginMsg::GetMetadata() const {
  return GetMetadataStatic();
}


// @@protoc_insertion_point(namespace_scope)
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::MyMsgHead* Arena::CreateMaybeMessage< ::MyMsgHead >(Arena* arena) {
  return Arena::CreateMessageInternal< ::MyMsgHead >(arena);
}
template<> PROTOBUF_NOINLINE ::MyLoginMsg* Arena::CreateMaybeMessage< ::MyLoginMsg >(Arena* arena) {
  return Arena::CreateMessageInternal< ::MyLoginMsg >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
