// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ortools/constraint_solver/solver_parameters.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_ortools_2fconstraint_5fsolver_2fsolver_5fparameters_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_ortools_2fconstraint_5fsolver_2fsolver_5fparameters_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3009000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3009000 < PROTOBUF_MIN_PROTOC_VERSION
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
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_ortools_2fconstraint_5fsolver_2fsolver_5fparameters_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_ortools_2fconstraint_5fsolver_2fsolver_5fparameters_2eproto {
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTableField entries[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::AuxillaryParseTableField aux[]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::ParseTable schema[1]
    PROTOBUF_SECTION_VARIABLE(protodesc_cold);
  static const ::PROTOBUF_NAMESPACE_ID::internal::FieldMetadata field_metadata[];
  static const ::PROTOBUF_NAMESPACE_ID::internal::SerializationTable serialization_table[];
  static const ::PROTOBUF_NAMESPACE_ID::uint32 offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ortools_2fconstraint_5fsolver_2fsolver_5fparameters_2eproto;
namespace operations_research {
class ConstraintSolverParameters;
class ConstraintSolverParametersDefaultTypeInternal;
extern ConstraintSolverParametersDefaultTypeInternal _ConstraintSolverParameters_default_instance_;
}  // namespace operations_research
PROTOBUF_NAMESPACE_OPEN
template<> ::operations_research::ConstraintSolverParameters* Arena::CreateMaybeMessage<::operations_research::ConstraintSolverParameters>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace operations_research {

enum ConstraintSolverParameters_TrailCompression : int {
  ConstraintSolverParameters_TrailCompression_NO_COMPRESSION = 0,
  ConstraintSolverParameters_TrailCompression_COMPRESS_WITH_ZLIB = 1,
  ConstraintSolverParameters_TrailCompression_ConstraintSolverParameters_TrailCompression_INT_MIN_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::min(),
  ConstraintSolverParameters_TrailCompression_ConstraintSolverParameters_TrailCompression_INT_MAX_SENTINEL_DO_NOT_USE_ = std::numeric_limits<::PROTOBUF_NAMESPACE_ID::int32>::max()
};
bool ConstraintSolverParameters_TrailCompression_IsValid(int value);
constexpr ConstraintSolverParameters_TrailCompression ConstraintSolverParameters_TrailCompression_TrailCompression_MIN = ConstraintSolverParameters_TrailCompression_NO_COMPRESSION;
constexpr ConstraintSolverParameters_TrailCompression ConstraintSolverParameters_TrailCompression_TrailCompression_MAX = ConstraintSolverParameters_TrailCompression_COMPRESS_WITH_ZLIB;
constexpr int ConstraintSolverParameters_TrailCompression_TrailCompression_ARRAYSIZE = ConstraintSolverParameters_TrailCompression_TrailCompression_MAX + 1;

const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor* ConstraintSolverParameters_TrailCompression_descriptor();
template<typename T>
inline const std::string& ConstraintSolverParameters_TrailCompression_Name(T enum_t_value) {
  static_assert(::std::is_same<T, ConstraintSolverParameters_TrailCompression>::value ||
    ::std::is_integral<T>::value,
    "Incorrect type passed to function ConstraintSolverParameters_TrailCompression_Name.");
  return ::PROTOBUF_NAMESPACE_ID::internal::NameOfEnum(
    ConstraintSolverParameters_TrailCompression_descriptor(), enum_t_value);
}
inline bool ConstraintSolverParameters_TrailCompression_Parse(
    const std::string& name, ConstraintSolverParameters_TrailCompression* value) {
  return ::PROTOBUF_NAMESPACE_ID::internal::ParseNamedEnum<ConstraintSolverParameters_TrailCompression>(
    ConstraintSolverParameters_TrailCompression_descriptor(), name, value);
}
// ===================================================================

class ConstraintSolverParameters :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:operations_research.ConstraintSolverParameters) */ {
 public:
  ConstraintSolverParameters();
  virtual ~ConstraintSolverParameters();

  ConstraintSolverParameters(const ConstraintSolverParameters& from);
  ConstraintSolverParameters(ConstraintSolverParameters&& from) noexcept
    : ConstraintSolverParameters() {
    *this = ::std::move(from);
  }

  inline ConstraintSolverParameters& operator=(const ConstraintSolverParameters& from) {
    CopyFrom(from);
    return *this;
  }
  inline ConstraintSolverParameters& operator=(ConstraintSolverParameters&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return GetMetadataStatic().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return GetMetadataStatic().reflection;
  }
  static const ConstraintSolverParameters& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const ConstraintSolverParameters* internal_default_instance() {
    return reinterpret_cast<const ConstraintSolverParameters*>(
               &_ConstraintSolverParameters_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(ConstraintSolverParameters& a, ConstraintSolverParameters& b) {
    a.Swap(&b);
  }
  inline void Swap(ConstraintSolverParameters* other) {
    if (other == this) return;
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  inline ConstraintSolverParameters* New() const final {
    return CreateMaybeMessage<ConstraintSolverParameters>(nullptr);
  }

  ConstraintSolverParameters* New(::PROTOBUF_NAMESPACE_ID::Arena* arena) const final {
    return CreateMaybeMessage<ConstraintSolverParameters>(arena);
  }
  void CopyFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void MergeFrom(const ::PROTOBUF_NAMESPACE_ID::Message& from) final;
  void CopyFrom(const ConstraintSolverParameters& from);
  void MergeFrom(const ConstraintSolverParameters& from);
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  #if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  #else
  bool MergePartialFromCodedStream(
      ::PROTOBUF_NAMESPACE_ID::io::CodedInputStream* input) final;
  #endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
  void SerializeWithCachedSizes(
      ::PROTOBUF_NAMESPACE_ID::io::CodedOutputStream* output) const final;
  ::PROTOBUF_NAMESPACE_ID::uint8* InternalSerializeWithCachedSizesToArray(
      ::PROTOBUF_NAMESPACE_ID::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  inline void SharedCtor();
  inline void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(ConstraintSolverParameters* other);
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "operations_research.ConstraintSolverParameters";
  }
  private:
  inline ::PROTOBUF_NAMESPACE_ID::Arena* GetArenaNoVirtual() const {
    return nullptr;
  }
  inline void* MaybeArenaPtr() const {
    return nullptr;
  }
  public:

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;
  private:
  static ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadataStatic() {
    ::PROTOBUF_NAMESPACE_ID::internal::AssignDescriptors(&::descriptor_table_ortools_2fconstraint_5fsolver_2fsolver_5fparameters_2eproto);
    return ::descriptor_table_ortools_2fconstraint_5fsolver_2fsolver_5fparameters_2eproto.file_level_metadata[kIndexInFileMessages];
  }

  public:

  // nested types ----------------------------------------------------

  typedef ConstraintSolverParameters_TrailCompression TrailCompression;
  static constexpr TrailCompression NO_COMPRESSION =
    ConstraintSolverParameters_TrailCompression_NO_COMPRESSION;
  static constexpr TrailCompression COMPRESS_WITH_ZLIB =
    ConstraintSolverParameters_TrailCompression_COMPRESS_WITH_ZLIB;
  static inline bool TrailCompression_IsValid(int value) {
    return ConstraintSolverParameters_TrailCompression_IsValid(value);
  }
  static constexpr TrailCompression TrailCompression_MIN =
    ConstraintSolverParameters_TrailCompression_TrailCompression_MIN;
  static constexpr TrailCompression TrailCompression_MAX =
    ConstraintSolverParameters_TrailCompression_TrailCompression_MAX;
  static constexpr int TrailCompression_ARRAYSIZE =
    ConstraintSolverParameters_TrailCompression_TrailCompression_ARRAYSIZE;
  static inline const ::PROTOBUF_NAMESPACE_ID::EnumDescriptor*
  TrailCompression_descriptor() {
    return ConstraintSolverParameters_TrailCompression_descriptor();
  }
  template<typename T>
  static inline const std::string& TrailCompression_Name(T enum_t_value) {
    static_assert(::std::is_same<T, TrailCompression>::value ||
      ::std::is_integral<T>::value,
      "Incorrect type passed to function TrailCompression_Name.");
    return ConstraintSolverParameters_TrailCompression_Name(enum_t_value);
  }
  static inline bool TrailCompression_Parse(const std::string& name,
      TrailCompression* value) {
    return ConstraintSolverParameters_TrailCompression_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  enum : int {
    kProfileFileFieldNumber = 8,
    kCompressTrailFieldNumber = 1,
    kTrailBlockSizeFieldNumber = 2,
    kArraySplitSizeFieldNumber = 3,
    kStoreNamesFieldNumber = 4,
    kNameCastVariablesFieldNumber = 5,
    kNameAllVariablesFieldNumber = 6,
    kProfilePropagationFieldNumber = 7,
    kPrintModelFieldNumber = 11,
    kPrintModelStatsFieldNumber = 12,
    kPrintAddedConstraintsFieldNumber = 13,
    kDisableSolveFieldNumber = 15,
    kProfileLocalSearchFieldNumber = 16,
    kPrintLocalSearchProfileFieldNumber = 17,
    kTracePropagationFieldNumber = 9,
    kTraceSearchFieldNumber = 10,
    kCheckSolutionPeriodFieldNumber = 114,
    kUseSmallTableFieldNumber = 101,
    kUseCumulativeEdgeFinderFieldNumber = 105,
    kUseCumulativeTimeTableFieldNumber = 106,
    kUseCumulativeTimeTableSyncFieldNumber = 112,
    kMaxEdgeFinderSizeFieldNumber = 109,
    kUseSequenceHighDemandTasksFieldNumber = 107,
    kUseAllPossibleDisjunctionsFieldNumber = 108,
    kDiffnUseCumulativeFieldNumber = 110,
    kUseElementRmqFieldNumber = 111,
    kSkipLocallyOptimalPathsFieldNumber = 113,
  };
  // string profile_file = 8;
  void clear_profile_file();
  const std::string& profile_file() const;
  void set_profile_file(const std::string& value);
  void set_profile_file(std::string&& value);
  void set_profile_file(const char* value);
  void set_profile_file(const char* value, size_t size);
  std::string* mutable_profile_file();
  std::string* release_profile_file();
  void set_allocated_profile_file(std::string* profile_file);

  // .operations_research.ConstraintSolverParameters.TrailCompression compress_trail = 1;
  void clear_compress_trail();
  ::operations_research::ConstraintSolverParameters_TrailCompression compress_trail() const;
  void set_compress_trail(::operations_research::ConstraintSolverParameters_TrailCompression value);

  // int32 trail_block_size = 2;
  void clear_trail_block_size();
  ::PROTOBUF_NAMESPACE_ID::int32 trail_block_size() const;
  void set_trail_block_size(::PROTOBUF_NAMESPACE_ID::int32 value);

  // int32 array_split_size = 3;
  void clear_array_split_size();
  ::PROTOBUF_NAMESPACE_ID::int32 array_split_size() const;
  void set_array_split_size(::PROTOBUF_NAMESPACE_ID::int32 value);

  // bool store_names = 4;
  void clear_store_names();
  bool store_names() const;
  void set_store_names(bool value);

  // bool name_cast_variables = 5;
  void clear_name_cast_variables();
  bool name_cast_variables() const;
  void set_name_cast_variables(bool value);

  // bool name_all_variables = 6;
  void clear_name_all_variables();
  bool name_all_variables() const;
  void set_name_all_variables(bool value);

  // bool profile_propagation = 7;
  void clear_profile_propagation();
  bool profile_propagation() const;
  void set_profile_propagation(bool value);

  // bool print_model = 11;
  void clear_print_model();
  bool print_model() const;
  void set_print_model(bool value);

  // bool print_model_stats = 12;
  void clear_print_model_stats();
  bool print_model_stats() const;
  void set_print_model_stats(bool value);

  // bool print_added_constraints = 13;
  void clear_print_added_constraints();
  bool print_added_constraints() const;
  void set_print_added_constraints(bool value);

  // bool disable_solve = 15;
  void clear_disable_solve();
  bool disable_solve() const;
  void set_disable_solve(bool value);

  // bool profile_local_search = 16;
  void clear_profile_local_search();
  bool profile_local_search() const;
  void set_profile_local_search(bool value);

  // bool print_local_search_profile = 17;
  void clear_print_local_search_profile();
  bool print_local_search_profile() const;
  void set_print_local_search_profile(bool value);

  // bool trace_propagation = 9;
  void clear_trace_propagation();
  bool trace_propagation() const;
  void set_trace_propagation(bool value);

  // bool trace_search = 10;
  void clear_trace_search();
  bool trace_search() const;
  void set_trace_search(bool value);

  // int32 check_solution_period = 114;
  void clear_check_solution_period();
  ::PROTOBUF_NAMESPACE_ID::int32 check_solution_period() const;
  void set_check_solution_period(::PROTOBUF_NAMESPACE_ID::int32 value);

  // bool use_small_table = 101;
  void clear_use_small_table();
  bool use_small_table() const;
  void set_use_small_table(bool value);

  // bool use_cumulative_edge_finder = 105;
  void clear_use_cumulative_edge_finder();
  bool use_cumulative_edge_finder() const;
  void set_use_cumulative_edge_finder(bool value);

  // bool use_cumulative_time_table = 106;
  void clear_use_cumulative_time_table();
  bool use_cumulative_time_table() const;
  void set_use_cumulative_time_table(bool value);

  // bool use_cumulative_time_table_sync = 112;
  void clear_use_cumulative_time_table_sync();
  bool use_cumulative_time_table_sync() const;
  void set_use_cumulative_time_table_sync(bool value);

  // int32 max_edge_finder_size = 109;
  void clear_max_edge_finder_size();
  ::PROTOBUF_NAMESPACE_ID::int32 max_edge_finder_size() const;
  void set_max_edge_finder_size(::PROTOBUF_NAMESPACE_ID::int32 value);

  // bool use_sequence_high_demand_tasks = 107;
  void clear_use_sequence_high_demand_tasks();
  bool use_sequence_high_demand_tasks() const;
  void set_use_sequence_high_demand_tasks(bool value);

  // bool use_all_possible_disjunctions = 108;
  void clear_use_all_possible_disjunctions();
  bool use_all_possible_disjunctions() const;
  void set_use_all_possible_disjunctions(bool value);

  // bool diffn_use_cumulative = 110;
  void clear_diffn_use_cumulative();
  bool diffn_use_cumulative() const;
  void set_diffn_use_cumulative(bool value);

  // bool use_element_rmq = 111;
  void clear_use_element_rmq();
  bool use_element_rmq() const;
  void set_use_element_rmq(bool value);

  // bool skip_locally_optimal_paths = 113;
  void clear_skip_locally_optimal_paths();
  bool skip_locally_optimal_paths() const;
  void set_skip_locally_optimal_paths(bool value);

  // @@protoc_insertion_point(class_scope:operations_research.ConstraintSolverParameters)
 private:
  class _Internal;

  ::PROTOBUF_NAMESPACE_ID::internal::InternalMetadataWithArena _internal_metadata_;
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr profile_file_;
  int compress_trail_;
  ::PROTOBUF_NAMESPACE_ID::int32 trail_block_size_;
  ::PROTOBUF_NAMESPACE_ID::int32 array_split_size_;
  bool store_names_;
  bool name_cast_variables_;
  bool name_all_variables_;
  bool profile_propagation_;
  bool print_model_;
  bool print_model_stats_;
  bool print_added_constraints_;
  bool disable_solve_;
  bool profile_local_search_;
  bool print_local_search_profile_;
  bool trace_propagation_;
  bool trace_search_;
  ::PROTOBUF_NAMESPACE_ID::int32 check_solution_period_;
  bool use_small_table_;
  bool use_cumulative_edge_finder_;
  bool use_cumulative_time_table_;
  bool use_cumulative_time_table_sync_;
  ::PROTOBUF_NAMESPACE_ID::int32 max_edge_finder_size_;
  bool use_sequence_high_demand_tasks_;
  bool use_all_possible_disjunctions_;
  bool diffn_use_cumulative_;
  bool use_element_rmq_;
  bool skip_locally_optimal_paths_;
  mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  friend struct ::TableStruct_ortools_2fconstraint_5fsolver_2fsolver_5fparameters_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ConstraintSolverParameters

// .operations_research.ConstraintSolverParameters.TrailCompression compress_trail = 1;
inline void ConstraintSolverParameters::clear_compress_trail() {
  compress_trail_ = 0;
}
inline ::operations_research::ConstraintSolverParameters_TrailCompression ConstraintSolverParameters::compress_trail() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.compress_trail)
  return static_cast< ::operations_research::ConstraintSolverParameters_TrailCompression >(compress_trail_);
}
inline void ConstraintSolverParameters::set_compress_trail(::operations_research::ConstraintSolverParameters_TrailCompression value) {
  
  compress_trail_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.compress_trail)
}

// int32 trail_block_size = 2;
inline void ConstraintSolverParameters::clear_trail_block_size() {
  trail_block_size_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 ConstraintSolverParameters::trail_block_size() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.trail_block_size)
  return trail_block_size_;
}
inline void ConstraintSolverParameters::set_trail_block_size(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  trail_block_size_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.trail_block_size)
}

// int32 array_split_size = 3;
inline void ConstraintSolverParameters::clear_array_split_size() {
  array_split_size_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 ConstraintSolverParameters::array_split_size() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.array_split_size)
  return array_split_size_;
}
inline void ConstraintSolverParameters::set_array_split_size(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  array_split_size_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.array_split_size)
}

// bool store_names = 4;
inline void ConstraintSolverParameters::clear_store_names() {
  store_names_ = false;
}
inline bool ConstraintSolverParameters::store_names() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.store_names)
  return store_names_;
}
inline void ConstraintSolverParameters::set_store_names(bool value) {
  
  store_names_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.store_names)
}

// bool name_cast_variables = 5;
inline void ConstraintSolverParameters::clear_name_cast_variables() {
  name_cast_variables_ = false;
}
inline bool ConstraintSolverParameters::name_cast_variables() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.name_cast_variables)
  return name_cast_variables_;
}
inline void ConstraintSolverParameters::set_name_cast_variables(bool value) {
  
  name_cast_variables_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.name_cast_variables)
}

// bool name_all_variables = 6;
inline void ConstraintSolverParameters::clear_name_all_variables() {
  name_all_variables_ = false;
}
inline bool ConstraintSolverParameters::name_all_variables() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.name_all_variables)
  return name_all_variables_;
}
inline void ConstraintSolverParameters::set_name_all_variables(bool value) {
  
  name_all_variables_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.name_all_variables)
}

// bool profile_propagation = 7;
inline void ConstraintSolverParameters::clear_profile_propagation() {
  profile_propagation_ = false;
}
inline bool ConstraintSolverParameters::profile_propagation() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.profile_propagation)
  return profile_propagation_;
}
inline void ConstraintSolverParameters::set_profile_propagation(bool value) {
  
  profile_propagation_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.profile_propagation)
}

// string profile_file = 8;
inline void ConstraintSolverParameters::clear_profile_file() {
  profile_file_.ClearToEmptyNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline const std::string& ConstraintSolverParameters::profile_file() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.profile_file)
  return profile_file_.GetNoArena();
}
inline void ConstraintSolverParameters::set_profile_file(const std::string& value) {
  
  profile_file_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.profile_file)
}
inline void ConstraintSolverParameters::set_profile_file(std::string&& value) {
  
  profile_file_.SetNoArena(
    &::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:operations_research.ConstraintSolverParameters.profile_file)
}
inline void ConstraintSolverParameters::set_profile_file(const char* value) {
  GOOGLE_DCHECK(value != nullptr);
  
  profile_file_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:operations_research.ConstraintSolverParameters.profile_file)
}
inline void ConstraintSolverParameters::set_profile_file(const char* value, size_t size) {
  
  profile_file_.SetNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:operations_research.ConstraintSolverParameters.profile_file)
}
inline std::string* ConstraintSolverParameters::mutable_profile_file() {
  
  // @@protoc_insertion_point(field_mutable:operations_research.ConstraintSolverParameters.profile_file)
  return profile_file_.MutableNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline std::string* ConstraintSolverParameters::release_profile_file() {
  // @@protoc_insertion_point(field_release:operations_research.ConstraintSolverParameters.profile_file)
  
  return profile_file_.ReleaseNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited());
}
inline void ConstraintSolverParameters::set_allocated_profile_file(std::string* profile_file) {
  if (profile_file != nullptr) {
    
  } else {
    
  }
  profile_file_.SetAllocatedNoArena(&::PROTOBUF_NAMESPACE_ID::internal::GetEmptyStringAlreadyInited(), profile_file);
  // @@protoc_insertion_point(field_set_allocated:operations_research.ConstraintSolverParameters.profile_file)
}

// bool profile_local_search = 16;
inline void ConstraintSolverParameters::clear_profile_local_search() {
  profile_local_search_ = false;
}
inline bool ConstraintSolverParameters::profile_local_search() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.profile_local_search)
  return profile_local_search_;
}
inline void ConstraintSolverParameters::set_profile_local_search(bool value) {
  
  profile_local_search_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.profile_local_search)
}

// bool print_local_search_profile = 17;
inline void ConstraintSolverParameters::clear_print_local_search_profile() {
  print_local_search_profile_ = false;
}
inline bool ConstraintSolverParameters::print_local_search_profile() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.print_local_search_profile)
  return print_local_search_profile_;
}
inline void ConstraintSolverParameters::set_print_local_search_profile(bool value) {
  
  print_local_search_profile_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.print_local_search_profile)
}

// bool trace_propagation = 9;
inline void ConstraintSolverParameters::clear_trace_propagation() {
  trace_propagation_ = false;
}
inline bool ConstraintSolverParameters::trace_propagation() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.trace_propagation)
  return trace_propagation_;
}
inline void ConstraintSolverParameters::set_trace_propagation(bool value) {
  
  trace_propagation_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.trace_propagation)
}

// bool trace_search = 10;
inline void ConstraintSolverParameters::clear_trace_search() {
  trace_search_ = false;
}
inline bool ConstraintSolverParameters::trace_search() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.trace_search)
  return trace_search_;
}
inline void ConstraintSolverParameters::set_trace_search(bool value) {
  
  trace_search_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.trace_search)
}

// bool print_model = 11;
inline void ConstraintSolverParameters::clear_print_model() {
  print_model_ = false;
}
inline bool ConstraintSolverParameters::print_model() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.print_model)
  return print_model_;
}
inline void ConstraintSolverParameters::set_print_model(bool value) {
  
  print_model_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.print_model)
}

// bool print_model_stats = 12;
inline void ConstraintSolverParameters::clear_print_model_stats() {
  print_model_stats_ = false;
}
inline bool ConstraintSolverParameters::print_model_stats() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.print_model_stats)
  return print_model_stats_;
}
inline void ConstraintSolverParameters::set_print_model_stats(bool value) {
  
  print_model_stats_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.print_model_stats)
}

// bool print_added_constraints = 13;
inline void ConstraintSolverParameters::clear_print_added_constraints() {
  print_added_constraints_ = false;
}
inline bool ConstraintSolverParameters::print_added_constraints() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.print_added_constraints)
  return print_added_constraints_;
}
inline void ConstraintSolverParameters::set_print_added_constraints(bool value) {
  
  print_added_constraints_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.print_added_constraints)
}

// bool disable_solve = 15;
inline void ConstraintSolverParameters::clear_disable_solve() {
  disable_solve_ = false;
}
inline bool ConstraintSolverParameters::disable_solve() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.disable_solve)
  return disable_solve_;
}
inline void ConstraintSolverParameters::set_disable_solve(bool value) {
  
  disable_solve_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.disable_solve)
}

// bool use_small_table = 101;
inline void ConstraintSolverParameters::clear_use_small_table() {
  use_small_table_ = false;
}
inline bool ConstraintSolverParameters::use_small_table() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.use_small_table)
  return use_small_table_;
}
inline void ConstraintSolverParameters::set_use_small_table(bool value) {
  
  use_small_table_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.use_small_table)
}

// bool use_cumulative_edge_finder = 105;
inline void ConstraintSolverParameters::clear_use_cumulative_edge_finder() {
  use_cumulative_edge_finder_ = false;
}
inline bool ConstraintSolverParameters::use_cumulative_edge_finder() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.use_cumulative_edge_finder)
  return use_cumulative_edge_finder_;
}
inline void ConstraintSolverParameters::set_use_cumulative_edge_finder(bool value) {
  
  use_cumulative_edge_finder_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.use_cumulative_edge_finder)
}

// bool use_cumulative_time_table = 106;
inline void ConstraintSolverParameters::clear_use_cumulative_time_table() {
  use_cumulative_time_table_ = false;
}
inline bool ConstraintSolverParameters::use_cumulative_time_table() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.use_cumulative_time_table)
  return use_cumulative_time_table_;
}
inline void ConstraintSolverParameters::set_use_cumulative_time_table(bool value) {
  
  use_cumulative_time_table_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.use_cumulative_time_table)
}

// bool use_cumulative_time_table_sync = 112;
inline void ConstraintSolverParameters::clear_use_cumulative_time_table_sync() {
  use_cumulative_time_table_sync_ = false;
}
inline bool ConstraintSolverParameters::use_cumulative_time_table_sync() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.use_cumulative_time_table_sync)
  return use_cumulative_time_table_sync_;
}
inline void ConstraintSolverParameters::set_use_cumulative_time_table_sync(bool value) {
  
  use_cumulative_time_table_sync_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.use_cumulative_time_table_sync)
}

// bool use_sequence_high_demand_tasks = 107;
inline void ConstraintSolverParameters::clear_use_sequence_high_demand_tasks() {
  use_sequence_high_demand_tasks_ = false;
}
inline bool ConstraintSolverParameters::use_sequence_high_demand_tasks() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.use_sequence_high_demand_tasks)
  return use_sequence_high_demand_tasks_;
}
inline void ConstraintSolverParameters::set_use_sequence_high_demand_tasks(bool value) {
  
  use_sequence_high_demand_tasks_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.use_sequence_high_demand_tasks)
}

// bool use_all_possible_disjunctions = 108;
inline void ConstraintSolverParameters::clear_use_all_possible_disjunctions() {
  use_all_possible_disjunctions_ = false;
}
inline bool ConstraintSolverParameters::use_all_possible_disjunctions() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.use_all_possible_disjunctions)
  return use_all_possible_disjunctions_;
}
inline void ConstraintSolverParameters::set_use_all_possible_disjunctions(bool value) {
  
  use_all_possible_disjunctions_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.use_all_possible_disjunctions)
}

// int32 max_edge_finder_size = 109;
inline void ConstraintSolverParameters::clear_max_edge_finder_size() {
  max_edge_finder_size_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 ConstraintSolverParameters::max_edge_finder_size() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.max_edge_finder_size)
  return max_edge_finder_size_;
}
inline void ConstraintSolverParameters::set_max_edge_finder_size(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  max_edge_finder_size_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.max_edge_finder_size)
}

// bool diffn_use_cumulative = 110;
inline void ConstraintSolverParameters::clear_diffn_use_cumulative() {
  diffn_use_cumulative_ = false;
}
inline bool ConstraintSolverParameters::diffn_use_cumulative() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.diffn_use_cumulative)
  return diffn_use_cumulative_;
}
inline void ConstraintSolverParameters::set_diffn_use_cumulative(bool value) {
  
  diffn_use_cumulative_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.diffn_use_cumulative)
}

// bool use_element_rmq = 111;
inline void ConstraintSolverParameters::clear_use_element_rmq() {
  use_element_rmq_ = false;
}
inline bool ConstraintSolverParameters::use_element_rmq() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.use_element_rmq)
  return use_element_rmq_;
}
inline void ConstraintSolverParameters::set_use_element_rmq(bool value) {
  
  use_element_rmq_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.use_element_rmq)
}

// bool skip_locally_optimal_paths = 113;
inline void ConstraintSolverParameters::clear_skip_locally_optimal_paths() {
  skip_locally_optimal_paths_ = false;
}
inline bool ConstraintSolverParameters::skip_locally_optimal_paths() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.skip_locally_optimal_paths)
  return skip_locally_optimal_paths_;
}
inline void ConstraintSolverParameters::set_skip_locally_optimal_paths(bool value) {
  
  skip_locally_optimal_paths_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.skip_locally_optimal_paths)
}

// int32 check_solution_period = 114;
inline void ConstraintSolverParameters::clear_check_solution_period() {
  check_solution_period_ = 0;
}
inline ::PROTOBUF_NAMESPACE_ID::int32 ConstraintSolverParameters::check_solution_period() const {
  // @@protoc_insertion_point(field_get:operations_research.ConstraintSolverParameters.check_solution_period)
  return check_solution_period_;
}
inline void ConstraintSolverParameters::set_check_solution_period(::PROTOBUF_NAMESPACE_ID::int32 value) {
  
  check_solution_period_ = value;
  // @@protoc_insertion_point(field_set:operations_research.ConstraintSolverParameters.check_solution_period)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace operations_research

PROTOBUF_NAMESPACE_OPEN

template <> struct is_proto_enum< ::operations_research::ConstraintSolverParameters_TrailCompression> : ::std::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::operations_research::ConstraintSolverParameters_TrailCompression>() {
  return ::operations_research::ConstraintSolverParameters_TrailCompression_descriptor();
}

PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_ortools_2fconstraint_5fsolver_2fsolver_5fparameters_2eproto
