// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: myMessage.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_myMessage_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_myMessage_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3019000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3019004 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_myMessage_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_myMessage_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxiliaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_myMessage_2eproto;
class MyMessage;
struct MyMessageDefaultTypeInternal;
extern MyMessageDefaultTypeInternal _MyMessage_default_instance_;
PROTOBUF_NAMESPACE_OPEN
template<> ::MyMessage* Arena::CreateMaybeMessage<::MyMessage>(Arena*);
PROTOBUF_NAMESPACE_CLOSE

// ===================================================================

class MyMessage final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:MyMessage) */ {
 public:
  inline MyMessage() : MyMessage(nullptr) {}
  ~MyMessage() override;
  explicit constexpr MyMessage(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  MyMessage(const MyMessage& from);
  MyMessage(MyMessage&& from) noexcept
    : MyMessage() {
    *this = ::std::move(from);
  }

  inline MyMessage& operator=(const MyMessage& from) {
    CopyFrom(from);
    return *this;
  }
  inline MyMessage& operator=(MyMessage&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const MyMessage& default_instance() {
    return *internal_default_instance();
  }
  static inline const MyMessage* internal_default_instance() {
    return reinterpret_cast<const MyMessage*>(
               &_MyMessage_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(MyMessage& a, MyMessage& b) {
    a.Swap(&b);
  }
  inline void Swap(MyMessage* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(MyMessage* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  MyMessage* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<MyMessage>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const MyMessage& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom(const MyMessage& from);
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message* to, const ::PROTOBUF_NAMESPACE_ID::Message& from);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(MyMessage* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "MyMessage";
  }
  protected:
  explicit MyMessage(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  private:
  static void ArenaDtor(void* object);
  inline void RegisterArenaDtor(::PROTOBUF_NAMESPACE_ID::Arena* arena);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kPhoneFieldNumber = 5,
    kInfoFieldNumber = 4,
    kNameFieldNumber = 1,
    kAgeFieldNumber = 2,
    kSexFieldNumber = 3,
  };
  // repeated int32 phone = 5;
  int phone_size() const;
  private:
  int _internal_phone_size() const;
  public:
  void clear_phone();
  private:
  int32_t _internal_phone(int index) const;
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
      _internal_phone() const;
  void _internal_add_phone(int32_t value);
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
      _internal_mutable_phone();
  public:
  int32_t phone(int index) const;
  void set_phone(int index, int32_t value);
  void add_phone(int32_t value);
  const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
      phone() const;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
      mutable_phone();

  // string info = 4;
  void clear_info();
  const std::string& info() const;
  template <typename ArgT0 = const std::string&, typename... ArgT>
  void set_info(ArgT0&& arg0, ArgT... args);
  std::string* mutable_info();
  PROTOBUF_NODISCARD std::string* release_info();
  void set_allocated_info(std::string* info);
  private:
  const std::string& _internal_info() const;
  inline PROTOBUF_ALWAYS_INLINE void _internal_set_info(const std::string& value);
  std::string* _internal_mutable_info();
  public:

  // int32 name = 1;
  void clear_name();
  int32_t name() const;
  void set_name(int32_t value);
  private:
  int32_t _internal_name() const;
  void _internal_set_name(int32_t value);
  public:

  // int32 age = 2;
  void clear_age();
  int32_t age() const;
  void set_age(int32_t value);
  private:
  int32_t _internal_age() const;
  void _internal_set_age(int32_t value);
  public:

  // bool sex = 3;
  void clear_sex();
  bool sex() const;
  void set_sex(bool value);
  private:
  bool _internal_sex() const;
  void _internal_set_sex(bool value);
  public:

  // @@protoc_insertion_point(class_scope:MyMessage)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t > phone_;
  mutable std::atomic<int> _phone_cached_byte_size_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr info_;
  int32_t name_;
  int32_t age_;
  bool sex_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_myMessage_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// MyMessage

// int32 name = 1;
inline void MyMessage::clear_name() {
  name_ = 0;
}
inline int32_t MyMessage::_internal_name() const {
  return name_;
}
inline int32_t MyMessage::name() const {
  // @@protoc_insertion_point(field_get:MyMessage.name)
  return _internal_name();
}
inline void MyMessage::_internal_set_name(int32_t value) {
  
  name_ = value;
}
inline void MyMessage::set_name(int32_t value) {
  _internal_set_name(value);
  // @@protoc_insertion_point(field_set:MyMessage.name)
}

// int32 age = 2;
inline void MyMessage::clear_age() {
  age_ = 0;
}
inline int32_t MyMessage::_internal_age() const {
  return age_;
}
inline int32_t MyMessage::age() const {
  // @@protoc_insertion_point(field_get:MyMessage.age)
  return _internal_age();
}
inline void MyMessage::_internal_set_age(int32_t value) {
  
  age_ = value;
}
inline void MyMessage::set_age(int32_t value) {
  _internal_set_age(value);
  // @@protoc_insertion_point(field_set:MyMessage.age)
}

// bool sex = 3;
inline void MyMessage::clear_sex() {
  sex_ = false;
}
inline bool MyMessage::_internal_sex() const {
  return sex_;
}
inline bool MyMessage::sex() const {
  // @@protoc_insertion_point(field_get:MyMessage.sex)
  return _internal_sex();
}
inline void MyMessage::_internal_set_sex(bool value) {
  
  sex_ = value;
}
inline void MyMessage::set_sex(bool value) {
  _internal_set_sex(value);
  // @@protoc_insertion_point(field_set:MyMessage.sex)
}

// string info = 4;
inline void MyMessage::clear_info() {
  info_.ClearToEmpty();
}
inline const std::string& MyMessage::info() const {
  // @@protoc_insertion_point(field_get:MyMessage.info)
  return _internal_info();
}
template <typename ArgT0, typename... ArgT>
inline PROTOBUF_ALWAYS_INLINE
void MyMessage::set_info(ArgT0&& arg0, ArgT... args) {
 
 info_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, static_cast<ArgT0 &&>(arg0), args..., GetArenaForAllocation());
  // @@protoc_insertion_point(field_set:MyMessage.info)
}
inline std::string* MyMessage::mutable_info() {
  std::string* _s = _internal_mutable_info();
  // @@protoc_insertion_point(field_mutable:MyMessage.info)
  return _s;
}
inline const std::string& MyMessage::_internal_info() const {
  return info_.Get();
}
inline void MyMessage::_internal_set_info(const std::string& value) {
  
  info_.Set(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, value, GetArenaForAllocation());
}
inline std::string* MyMessage::_internal_mutable_info() {
  
  return info_.Mutable(::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::EmptyDefault{}, GetArenaForAllocation());
}
inline std::string* MyMessage::release_info() {
  // @@protoc_insertion_point(field_release:MyMessage.info)
  return info_.Release(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), GetArenaForAllocation());
}
inline void MyMessage::set_allocated_info(std::string* info) {
  if (info != nullptr) {
    
  } else {
    
  }
  info_.SetAllocated(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), info,
      GetArenaForAllocation());
#ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (info_.IsDefault(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited())) {
    info_.Set(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), "", GetArenaForAllocation());
  }
#endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  // @@protoc_insertion_point(field_set_allocated:MyMessage.info)
}

// repeated int32 phone = 5;
inline int MyMessage::_internal_phone_size() const {
  return phone_.size();
}
inline int MyMessage::phone_size() const {
  return _internal_phone_size();
}
inline void MyMessage::clear_phone() {
  phone_.Clear();
}
inline int32_t MyMessage::_internal_phone(int index) const {
  return phone_.Get(index);
}
inline int32_t MyMessage::phone(int index) const {
  // @@protoc_insertion_point(field_get:MyMessage.phone)
  return _internal_phone(index);
}
inline void MyMessage::set_phone(int index, int32_t value) {
  phone_.Set(index, value);
  // @@protoc_insertion_point(field_set:MyMessage.phone)
}
inline void MyMessage::_internal_add_phone(int32_t value) {
  phone_.Add(value);
}
inline void MyMessage::add_phone(int32_t value) {
  _internal_add_phone(value);
  // @@protoc_insertion_point(field_add:MyMessage.phone)
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
MyMessage::_internal_phone() const {
  return phone_;
}
inline const ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >&
MyMessage::phone() const {
  // @@protoc_insertion_point(field_list:MyMessage.phone)
  return _internal_phone();
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
MyMessage::_internal_mutable_phone() {
  return &phone_;
}
inline ::PROTOBUF_NAMESPACE_ID::RepeatedField< int32_t >*
MyMessage::mutable_phone() {
  // @@protoc_insertion_point(field_mutable_list:MyMessage.phone)
  return _internal_mutable_phone();
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)


// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_myMessage_2eproto
