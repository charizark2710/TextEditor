/**
 * This file is part of the mingw-w64 runtime package.
 * No warranty is given; refer to the file DISCLAIMER within this package.
 */
#ifndef _BDATYPES_
#define _BDATYPES_ 1

#include <winapifamily.h>

#if WINAPI_FAMILY_PARTITION (WINAPI_PARTITION_DESKTOP)

#define BDA_PLP_ID_NOT_SET -1

#define MIN_DIMENSION 1

typedef LONG PBDARESULT;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum BDA_EVENT_ID {
  BDA_EVENT_SIGNAL_LOSS = 0,
  BDA_EVENT_SIGNAL_LOCK,
  BDA_EVENT_DATA_START,
  BDA_EVENT_DATA_STOP,
  BDA_EVENT_CHANNEL_ACQUIRED,
  BDA_EVENT_CHANNEL_LOST,
  BDA_EVENT_CHANNEL_SOURCE_CHANGED,
  BDA_EVENT_CHANNEL_ACTIVATED,
  BDA_EVENT_CHANNEL_DEACTIVATED,
  BDA_EVENT_SUBCHANNEL_ACQUIRED,
  BDA_EVENT_SUBCHANNEL_LOST,
  BDA_EVENT_SUBCHANNEL_SOURCE_CHANGED,
  BDA_EVENT_SUBCHANNEL_ACTIVATED,
  BDA_EVENT_SUBCHANNEL_DEACTIVATED,
  BDA_EVENT_ACCESS_GRANTED,
  BDA_EVENT_ACCESS_DENIED,
  BDA_EVENT_OFFER_EXTENDED,
  BDA_EVENT_PURCHASE_COMPLETED,
  BDA_EVENT_SMART_CARD_INSERTED,
  BDA_EVENT_SMART_CARD_REMOVED
} BDA_EVENT_ID, *PBDA_EVENT_ID;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum BDA_MULTICAST_MODE {
  BDA_PROMISCUOUS_MULTICAST = 0,
  BDA_FILTERED_MULTICAST,
  BDA_NO_MULTICAST
} BDA_MULTICAST_MODE, *PBDA_MULTICAST_MODE;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum BDA_SIGNAL_STATE {
  BDA_SIGNAL_UNAVAILABLE = 0,
  BDA_SIGNAL_INACTIVE,
  BDA_SIGNAL_ACTIVE
} BDA_SIGNAL_STATE, *PBDA_SIGNAL_STATE;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum BDA_CHANGE_STATE {
  BDA_CHANGES_COMPLETE = 0,
  BDA_CHANGES_PENDING
} BDA_CHANGE_STATE, *PBDA_CHANGE_STATE;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum MEDIA_SAMPLE_CONTENT {
  MEDIA_TRANSPORT_PACKET,
  MEDIA_ELEMENTARY_STREAM,
  MEDIA_MPEG2_PSI,
  MEDIA_TRANSPORT_PAYLOAD
} MEDIA_SAMPLE_CONTENT;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum ISDBCAS_REQUEST_ID {
  ISDBCAS_REQUEST_ID_EMG = 0x38,
  ISDBCAS_REQUEST_ID_EMD = 0x3a,
} ISDBCAS_REQUEST_ID;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum MUX_PID_TYPE {
  PID_OTHER = -1,
  PID_ELEMENTARY_STREAM,
  PID_MPEG2_SECTION_PSI_SI
} MUX_PID_TYPE;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum DVBSystemType {
  DVB_Cable,
  DVB_Terrestrial,
  DVB_Satellite,
  ISDB_Terrestrial,
  ISDB_Satellite
} DVBSystemType;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum BDA_Channel {
  BDA_UNDEFINED_CHANNEL = -1
} BDA_Channel;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum ComponentCategory {
  CategoryNotSet = -1,
  CategoryOther = 0,
  CategoryVideo,
  CategoryAudio,
  CategoryText,
  CategorySubtitles,
  CategoryCaptions,
  CategorySuperimpose,
  CategoryData,
  CATEGORY_COUNT
} ComponentCategory;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum ComponentStatus {
  StatusActive,
  StatusInactive,
  StatusUnavailable
} ComponentStatus;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum MPEG2StreamType {
  BDA_UNITIALIZED_MPEG2STREAMTYPE = -1,
  Reserved1 = 0x00,
  ISO_IEC_11172_2_VIDEO = 0x01,
  ISO_IEC_13818_2_VIDEO = 0x02,
  ISO_IEC_11172_3_AUDIO = 0x03,
  ISO_IEC_13818_3_AUDIO = 0x04,
  ISO_IEC_13818_1_PRIVATE_SECTION = 0x05,
  ISO_IEC_13818_1_PES = 0x06,
  ISO_IEC_13522_MHEG = 0x07,
  ANNEX_A_DSM_CC = 0x08,
  ITU_T_REC_H_222_1 = 0x09,
  ISO_IEC_13818_6_TYPE_A = 0x0a,
  ISO_IEC_13818_6_TYPE_B = 0x0b,
  ISO_IEC_13818_6_TYPE_C = 0x0c,
  ISO_IEC_13818_6_TYPE_D = 0x0d,
  ISO_IEC_13818_1_AUXILIARY = 0x0e,
  ISO_IEC_13818_7_AUDIO = 0x0f,
  ISO_IEC_14496_2_VISUAL = 0x10,
  ISO_IEC_14496_3_AUDIO = 0x11,
  ISO_IEC_14496_1_IN_PES = 0x12,
  ISO_IEC_14496_1_IN_SECTION = 0x13,
  ISO_IEC_13818_6_DOWNLOAD = 0x14,
  METADATA_IN_PES = 0x15,
  METADATA_IN_SECTION = 0x16,
  METADATA_IN_DATA_CAROUSEL = 0x17,
  METADATA_IN_OBJECT_CAROUSEL = 0x18,
  METADATA_IN_DOWNLOAD_PROTOCOL = 0x19,
  IRPM_STREAMM = 0x1a,
  ITU_T_H264 = 0x1b,
  ISO_IEC_13818_1_RESERVED = 0x1c,
  USER_PRIVATE = 0x10,
  ISO_IEC_USER_PRIVATE = 0x80,
  DOLBY_AC3_AUDIO = 0x81,
  DOLBY_DIGITAL_PLUS_AUDIO_ATSC = 0x87
} MPEG2StreamType;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum ATSCComponentTypeFlags {
  ATSCCT_AC3 = 0x1
} ATSCComponentTypeFlags;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum BinaryConvolutionCodeRate {
  BDA_BCC_RATE_NOT_SET = -1,
  BDA_BCC_RATE_NOT_DEFINED = 0,
  BDA_BCC_RATE_1_2 = 1,
  BDA_BCC_RATE_2_3,
  BDA_BCC_RATE_3_4,
  BDA_BCC_RATE_3_5,
  BDA_BCC_RATE_4_5,
  BDA_BCC_RATE_5_6,
  BDA_BCC_RATE_5_11,
  BDA_BCC_RATE_7_8,
  BDA_BCC_RATE_1_4,
  BDA_BCC_RATE_1_3,
  BDA_BCC_RATE_2_5,
  BDA_BCC_RATE_6_7,
  BDA_BCC_RATE_8_9,
  BDA_BCC_RATE_9_10,
  BDA_BCC_RATE_MAX
} BinaryConvolutionCodeRate;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum FECMethod {
  BDA_FEC_METHOD_NOT_SET = -1,
  BDA_FEC_METHOD_NOT_DEFINED = 0,
  BDA_FEC_VITERBI = 1,
  BDA_FEC_RS_204_188,
  BDA_FEC_LDPC,
  BDA_FEC_BCH,
  BDA_FEC_RS_147_130,
  BDA_FEC_MAX
} FECMethod;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum ModulationType {
  BDA_MOD_NOT_SET = -1,
  BDA_MOD_NOT_DEFINED = 0,
  BDA_MOD_16QAM = 1,
  BDA_MOD_32QAM,
  BDA_MOD_64QAM,
  BDA_MOD_80QAM,
  BDA_MOD_96QAM,
  BDA_MOD_112QAM,
  BDA_MOD_128QAM,
  BDA_MOD_160QAM,
  BDA_MOD_192QAM,
  BDA_MOD_224QAM,
  BDA_MOD_256QAM,
  BDA_MOD_320QAM,
  BDA_MOD_384QAM,
  BDA_MOD_448QAM,
  BDA_MOD_512QAM,
  BDA_MOD_640QAM,
  BDA_MOD_768QAM,
  BDA_MOD_896QAM,
  BDA_MOD_1024QAM,
  BDA_MOD_QPSK,
  BDA_MOD_BPSK,
  BDA_MOD_OQPSK,
  BDA_MOD_8VSB,
  BDA_MOD_16VSB,
  BDA_MOD_ANALOG_AMPLITUDE,
  BDA_MOD_ANALOG_FREQUENCY,
  BDA_MOD_8PSK,
  BDA_MOD_RF,
  BDA_MOD_16APSK,
  BDA_MOD_32APSK,
  BDA_MOD_NBC_QPSK,
  BDA_MOD_NBC_8PSK,
  BDA_MOD_DIRECTV,
  BDA_MOD_ISDB_T_TMCC,
  BDA_MOD_ISDB_S_TMCC,
  BDA_MOD_MAX
} ModulationType;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum tagScanModulationTypes {
  BDA_SCAN_MOD_16QAM = 0x00000001,
  BDA_SCAN_MOD_32QAM = 0x00000002,
  BDA_SCAN_MOD_64QAM = 0x00000004,
  BDA_SCAN_MOD_80QAM = 0x00000008,
  BDA_SCAN_MOD_96QAM = 0x00000010,
  BDA_SCAN_MOD_112QAM = 0x00000020,
  BDA_SCAN_MOD_128QAM = 0x00000040,
  BDA_SCAN_MOD_160QAM = 0x00000080,
  BDA_SCAN_MOD_192QAM = 0x00000100,
  BDA_SCAN_MOD_224QAM = 0x00000200,
  BDA_SCAN_MOD_256QAM = 0x00000400,
  BDA_SCAN_MOD_320QAM = 0x00000800,
  BDA_SCAN_MOD_384QAM = 0x00001000,
  BDA_SCAN_MOD_448QAM = 0x00002000,
  BDA_SCAN_MOD_512QAM = 0x00004000,
  BDA_SCAN_MOD_640QAM = 0x00008000,
  BDA_SCAN_MOD_768QAM = 0x00010000,
  BDA_SCAN_MOD_896QAM = 0x00020000,
  BDA_SCAN_MOD_1024QAM = 0x00040000,
  BDA_SCAN_MOD_QPSK = 0x00080000,
  BDA_SCAN_MOD_BPSK = 0x00100000,
  BDA_SCAN_MOD_OQPSK = 0x00200000,
  BDA_SCAN_MOD_8VSB = 0x00400000,
  BDA_SCAN_MOD_16VSB = 0x00800000,
  BDA_SCAN_MOD_AM_RADIO = 0x01000000,
  BDA_SCAN_MOD_FM_RADIO = 0x02000000,
  BDA_SCAN_MOD_8PSK = 0x04000000,
  BDA_SCAN_MOD_RF = 0x08000000,
  ScanModulationTypesMask_MCE_DigitalCable = BDA_MOD_64QAM |
  BDA_MOD_256QAM,
  ScanModulationTypesMask_MCE_TerrestrialATSC = BDA_MOD_8VSB,
  ScanModulationTypesMask_MCE_AnalogTv = BDA_MOD_RF,
  ScanModulationTypesMask_MCE_All_TV = 0xffffffff,
  ScanModulationTypesMask_DVBC = BDA_MOD_64QAM | BDA_SCAN_MOD_128QAM |
  BDA_MOD_256QAM,
  BDA_SCAN_MOD_16APSK = 0x10000000,
  BDA_SCAN_MOD_32APSK = 0x20000000,
} ScanModulationTypes;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum SpectralInversion {
  BDA_SPECTRAL_INVERSION_NOT_SET = -1,
  BDA_SPECTRAL_INVERSION_NOT_DEFINED = 0,
  BDA_SPECTRAL_INVERSION_AUTOMATIC = 1,
  BDA_SPECTRAL_INVERSION_NORMAL,
  BDA_SPECTRAL_INVERSION_INVERTED,
  BDA_SPECTRAL_INVERSION_MAX
} SpectralInversion;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum Polarisation {
  BDA_POLARISATION_NOT_SET = -1,
  BDA_POLARISATION_NOT_DEFINED = 0,
  BDA_POLARISATION_LINEAR_H = 1,
  BDA_POLARISATION_LINEAR_V,
  BDA_POLARISATION_CIRCULAR_L,
  BDA_POLARISATION_CIRCULAR_R,
  BDA_POLARISATION_MAX
} Polarisation;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum LNB_Source {
  BDA_LNB_SOURCE_NOT_SET = -1,
  BDA_LNB_SOURCE_NOT_DEFINED = 0,
  BDA_LNB_SOURCE_A = 1,
  BDA_LNB_SOURCE_B = 2,
  BDA_LNB_SOURCE_C = 3,
  BDA_LNB_SOURCE_D = 4,
  BDA_LNB_SOURCE_MAX
} LNB_Source;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum GuardInterval {
  BDA_GUARD_NOT_SET = -1,
  BDA_GUARD_NOT_DEFINED = 0,
  BDA_GUARD_1_32 = 1,
  BDA_GUARD_1_16,
  BDA_GUARD_1_8,
  BDA_GUARD_1_4,
  BDA_GUARD_1_128,
  BDA_GUARD_19_128,
  BDA_GUARD_19_256,
  BDA_GUARD_MAX
} GuardInterval;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum HierarchyAlpha {
  BDA_HALPHA_NOT_SET = -1,
  BDA_HALPHA_NOT_DEFINED = 0,
  BDA_HALPHA_1 = 1,
  BDA_HALPHA_2,
  BDA_HALPHA_4,
  BDA_HALPHA_MAX
} HierarchyAlpha;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum TransmissionMode {
  BDA_XMIT_MODE_NOT_SET = -1,
  BDA_XMIT_MODE_NOT_DEFINED = 0,
  BDA_XMIT_MODE_2K = 1,
  BDA_XMIT_MODE_8K,
  BDA_XMIT_MODE_4K,
  BDA_XMIT_MODE_2K_INTERLEAVED,
  BDA_XMIT_MODE_4K_INTERLEAVED,
  BDA_XMIT_MODE_1K,
  BDA_XMIT_MODE_16K,
  BDA_XMIT_MODE_32K,
  BDA_XMIT_MODE_MAX
} TransmissionMode;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum RollOff {
  BDA_ROLL_OFF_NOT_SET = -1,
  BDA_ROLL_OFF_NOT_DEFINED = 0,
  BDA_ROLL_OFF_20 = 1,
  BDA_ROLL_OFF_25,
  BDA_ROLL_OFF_35,
  BDA_ROLL_OFF_MAX
} RollOff;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum Pilot {
  BDA_PILOT_NOT_SET = -1,
  BDA_PILOT_NOT_DEFINED = 0,
  BDA_PILOT_OFF = 1,
  BDA_PILOT_ON,
  BDA_PILOT_MAX
} Pilot;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum BDA_Frequency {
  BDA_FREQUENCY_NOT_SET = -1,
  BDA_FREQUENCY_NOT_DEFINED = 0
} BDA_Frequency;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum BDA_Range {
  BDA_RANGE_NOT_SET = -1,
  BDA_RANGE_NOT_DEFINED = 0
} BDA_Range;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum BDA_Channel_Bandwidth {
  BDA_CHAN_BANDWITH_NOT_SET = -1,
  BDA_CHAN_BANDWITH_NOT_DEFINED = 0
} BDA_Channel_Bandwidth;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum BDA_Frequency_Multiplier {
  BDA_FREQUENCY_MULTIPLIER_NOT_SET = -1,
  BDA_FREQUENCY_MULTIPLIER_NOT_DEFINED = 0
} BDA_Frequency_Multiplier;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum BDA_Comp_Flags {
  BDACOMP_NOT_DEFINED = 0x00000000,
  BDACOMP_EXCLUDE_TS_FROM_TR = 0x00000001,
  BDACOMP_INCLUDE_LOCATOR_IN_TR = 0x00000002,
  BDACOMP_INCLUDE_COMPONENTS_IN_TR = 0x00000004
} BDA_Comp_Flags;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum ApplicationTypeType {
  SCTE28_ConditionalAccess = 0,
  SCTE28_POD_Host_Binding_Information,
  SCTE28_IPService,
  SCTE28_NetworkInterface_SCTE55_2,
  SCTE28_NetworkInterface_SCTE55_1,
  SCTE28_CopyProtection,
  SCTE28_Diagnostic,
  SCTE28_Undesignated,
  SCTE28_Reserved,
} ApplicationTypeType;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum BDA_CONDITIONALACCESS_REQUESTTYPE {
  CONDITIONALACCESS_ACCESS_UNSPECIFIED = 0,
  CONDITIONALACCESS_ACCESS_NOT_POSSIBLE,
  CONDITIONALACCESS_ACCESS_POSSIBLE,
  CONDITIONALACCESS_ACCESS_POSSIBLE_NO_STREAMING_DISRUPTION
} BDA_CONDITIONALACCESS_REQUESTTYPE;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum BDA_CONDITIONALACCESS_MMICLOSEREASON {
  CONDITIONALACCESS_UNSPECIFIED = 0,
  CONDITIONALACCESS_CLOSED_ITSELF,
  CONDITIONALACCESS_TUNER_REQUESTED_CLOSE,
  CONDITIONALACCESS_DIALOG_TIMEOUT,
  CONDITIONALACCESS_DIALOG_FOCUS_CHANGE,
  CONDITIONALACCESS_DIALOG_USER_DISMISSED,
  CONDITIONALACCESS_DIALOG_USER_NOT_AVAILABLE
} BDA_CONDITIONALACCESS_MMICLOSEREASON;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum BDA_CONDITIONALACCESS_SESSION_RESULT {
  CONDITIONALACCESS_SUCCESSFULL = 0,
  CONDITIONALACCESS_ENDED_NOCHANGE,
  CONDITIONALACCESS_ABORTED
} BDA_CONDITIONALACCESS_SESSION_RESULT;

typedef
#ifdef __WIDL__
  [v1_enum]
#endif
  enum BDA_DISCOVERY_STATE {
  BDA_DISCOVERY_UNSPECIFIED = 0,
  BDA_DISCOVERY_REQUIRED,
  BDA_DISCOVERY_COMPLETE
} BDA_DISCOVERY_STATE;

typedef struct _BDA_TEMPLATE_CONNECTION {
  ULONG FromNodeType;
  ULONG FromNodePinType;
  ULONG ToNodeType;
  ULONG ToNodePinType;
} BDA_TEMPLATE_CONNECTION, *PBDA_TEMPLATE_CONNECTION;

typedef struct _BDA_TEMPLATE_PIN_JOINT {
  ULONG uliTemplateConnection;
  ULONG ulcInstancesMax;
} BDA_TEMPLATE_PIN_JOINT, *PBDA_TEMPLATE_PIN_JOINT;

typedef struct tagKS_BDA_FRAME_INFO {
  ULONG ExtendedHeaderSize;
  DWORD dwFrameFlags;
  ULONG ulEvent;
  ULONG ulChannelNumber;
  ULONG ulSubchannelNumber;
  ULONG ulReason;
} KS_BDA_FRAME_INFO, *PKS_BDA_FRAME_INFO;

typedef struct _BDA_ETHERNET_ADDRESS {
  BYTE rgbAddress[6];
} BDA_ETHERNET_ADDRESS, *PBDA_ETHERNET_ADDRESS;

typedef struct _BDA_ETHERNET_ADDRESS_LIST {
  ULONG ulcAddresses;
  BDA_ETHERNET_ADDRESS rgAddressl[MIN_DIMENSION];
} BDA_ETHERNET_ADDRESS_LIST, *PBDA_ETHERNET_ADDRESS_LIST;

typedef struct _BDA_IPv4_ADDRESS {
  BYTE rgbAddress[4];
} BDA_IPv4_ADDRESS, *PBDA_IPv4_ADDRESS;

typedef struct _BDA_IPv4_ADDRESS_LIST {
  ULONG ulcAddresses;
  BDA_IPv4_ADDRESS rgAddressl[MIN_DIMENSION];
} BDA_IPv4_ADDRESS_LIST, *PBDA_IPv4_ADDRESS_LIST;

typedef struct _BDA_IPv6_ADDRESS {
  BYTE rgbAddress[6];
} BDA_IPv6_ADDRESS, *PBDA_IPv6_ADDRESS;

typedef struct _BDA_IPv6_ADDRESS_LIST {
  ULONG ulcAddresses;
  BDA_IPv6_ADDRESS rgAddressl[MIN_DIMENSION];
} BDA_IPv6_ADDRESS_LIST, *PBDA_IPv6_ADDRESS_LIST;

typedef struct _BDANODE_DESCRIPTOR {
  ULONG ulBdaNodeType;
  GUID guidFunction;
  GUID guidName;
} BDANODE_DESCRIPTOR, *PBDANODE_DESCRIPTOR;

typedef struct _BDA_TABLE_SECTION {
  ULONG ulPrimarySectionId;
  ULONG ulSecondarySectionId;
  ULONG ulcbSectionLength;
  ULONG argbSectionData[MIN_DIMENSION];
} BDA_TABLE_SECTION, *PBDA_TABLE_SECTION;

typedef struct _BDA_DISEQC_SEND {
  ULONG ulRequestId;
  ULONG ulPacketLength;
  BYTE argbPacketData[8];
} BDA_DISEQC_SEND, *PBDA_DISEQC_SEND;

typedef struct _BDA_DISEQC_RESPONSE {
  ULONG ulRequestId;
  ULONG ulPacketLength;
  BYTE argbPacketData[8];
} BDA_DISEQC_RESPONSE, *PBDA_DISEQC_RESPONSE;

typedef struct {
  ULONG ulPID;
  MEDIA_SAMPLE_CONTENT MediaSampleContent;
} PID_MAP;

typedef struct _BDA_PID_MAP {
  MEDIA_SAMPLE_CONTENT MediaSampleContent;
  ULONG ulcPIDs;
  ULONG aulPIDs[MIN_DIMENSION];
} BDA_PID_MAP, *PBDA_PID_MAP;

typedef struct _BDA_PID_UNMAP {
  ULONG ulcPIDs;
  ULONG aulPIDs[MIN_DIMENSION];
} BDA_PID_UNMAP, *PBDA_PID_UNMAP;

typedef struct _BDA_CA_MODULE_UI {
  ULONG ulFormat;
  ULONG ulbcDesc;
  ULONG ulDesc[MIN_DIMENSION];
} BDA_CA_MODULE_UI, *PBDA_CA_MODULE_UI;

typedef struct _BDA_PROGRAM_PID_LIST {
  ULONG ulProgramNumber;
  ULONG ulcPIDs;
  ULONG ulPID[MIN_DIMENSION];
} BDA_PROGRAM_PID_LIST, *PBDA_PROGRAM_PID_LIST;

typedef struct _BDA_DRM_DRMSTATUS {
  PBDARESULT lResult;
  GUID DRMuuid;
  ULONG ulDrmUuidListStringSize;
  GUID argbDrmUuidListString[MIN_DIMENSION];
} BDA_DRM_DRMSTATUS, *PBDA_DRM_DRMSTATUS;

typedef struct _BDA_WMDRM_STATUS {
  PBDARESULT lResult;
  ULONG ulMaxCaptureTokenSize;
  ULONG uMaxStreamingPid;
  ULONG ulMaxLicense;
  ULONG ulMinSecurityLevel;
  ULONG ulRevInfoSequenceNumber;
  ULONGLONG ulRevInfoIssuedTime;
  ULONG ulRevListVersion;
  ULONG ulRevInfoTTL;
  ULONG ulState;
} BDA_WMDRM_STATUS, *PBDA_WMDRM_STATUS;

typedef struct _BDA_WMDRM_KEYINFOLIST {
  PBDARESULT lResult;
  ULONG ulKeyuuidBufferLen;
  GUID argKeyuuidBuffer[MIN_DIMENSION];
} BDA_WMDRM_KEYINFOLIST, *PBDA_WMDRM_KEYINFOLIST;

typedef struct _BDA_BUFFER {
  PBDARESULT lResult;
  ULONG ulBufferSize;
  BYTE argbBuffer[MIN_DIMENSION];
} BDA_BUFFER, *PBDA_BUFFER;

typedef struct _BDA_WMDRM_RENEWLICENSE {
  PBDARESULT lResult;
  ULONG ulDescrambleStatus;
  ULONG ulXmrLicenseOutputLength;
  BYTE argbXmrLicenceOutputBuffer[MIN_DIMENSION];
} BDA_WMDRM_RENEWLICENSE, *PBDA_WMDRM_RENEWLICENSE;

typedef struct _BDA_WMDRMTUNER_PIDPROTECTION {
  PBDARESULT lResult;
  GUID uuidKeyID;
} BDA_WMDRMTUNER_PIDPROTECTION, *PBDA_WMDRMTUNER_PIDPROTECTION;

typedef struct _BDA_WMDRMTUNER_PURCHASEENTITLEMENT {
  PBDARESULT lResult;
  ULONG ulDescrambleStatus;
  ULONG ulCaptureTokenLength;
  BYTE argbCaptureTokenBuffer[MIN_DIMENSION];
} BDA_WMDRMTUNER_PURCHASEENTITLEMENT, *PBDA_WMDRMTUNER_PURCHASEENTITLEMENT;

typedef struct _BDA_TUNER_TUNERSTATE {
  PBDARESULT lResult;
  ULONG ulTuneLength;
  BYTE argbTuneData [MIN_DIMENSION];
} BDA_TUNER_TUNERSTATE, *PBDA_TUNER_TUNERSTATE;

typedef struct _BDA_TUNER_DIAGNOSTICS {
  PBDARESULT lResult;
  ULONG ulSignalLevel;
  ULONG ulSignalLevelQuality;
  ULONG ulSignalNoiseRatio;
} BDA_TUNER_DIAGNOSTICS, *PBDA_TUNER_DIAGNOSTICS;

typedef struct _BDA_STRING {
  PBDARESULT lResult;
  ULONG ulStringSize;
  BYTE argbString[MIN_DIMENSION];
} BDA_STRING, *PBDA_STRING;

typedef struct _BDA_SCAN_CAPABILTIES {
  PBDARESULT lResult;
  UINT64 ul64AnalogStandardsSupported;
} BDA_SCAN_CAPABILTIES, *PBDA_SCAN_CAPABILTIES;

typedef struct _BDA_SCAN_STATE {
  PBDARESULT lResult;
  ULONG ulSignalLock;
  ULONG ulSecondsLeft;
  ULONG ulCurrentFrequency;
} BDA_SCAN_STATE, *PBDA_SCAN_STATE;

typedef struct _BDA_SCAN_START {
  PBDARESULT lResult;
  ULONG LowerFrequency;
  ULONG HigerFrequency;
} BDA_SCAN_START, *PBDA_SCAN_START;

typedef struct _BDA_GDDS_DATATYPE {
  PBDARESULT lResult;
  GUID uuidDataType;
} BDA_GDDS_DATATYPE, *P_BDA_GDDS_DATATYPE;

typedef struct _BDA_GDDS_DATA {
  PBDARESULT lResult;
  ULONG ulDataLength;
  ULONG ulPercentageProgress;
  BYTE argbData [MIN_DIMENSION];
} BDA_GDDS_DATA, *P_BDA_GDDS_DATA;

typedef struct _BDA_USERACTIVITY_INTERVAL {
  PBDARESULT lResult;
  ULONG ulActivityInterval;
} BDA_USERACTIVITY_INTERVAL, *P_BDA_USERACTIVITY_INTERVAL;

typedef struct _BDA_CAS_CHECK_ENTITLEMENTTOKEN {
  PBDARESULT lResult;
  ULONG ulDescrambleStatus;
} BDA_CAS_CHECK_ENTITLEMENTTOKEN, *PBDA_CAS_CHECK_ENTITLEMENTTOKEN;

typedef struct _BDA_CAS_CLOSE_MMIDIALOG {
  PBDARESULT lResult;
  ULONG SessionResult;
} BDA_CAS_CLOSE_MMIDIALOG, *PBDA_CAS_CLOSE_MMIDIALOG;

typedef struct _BDA_CAS_REQUESTTUNERDATA {
  UCHAR ucRequestPriority;
  UCHAR ucRequestReason;
  UCHAR ucRequestConsequences;
  ULONG ulEstimatedTime;
} BDA_CAS_REQUESTTUNERDATA, *PBDA_CAS_REQUESTTUNERDATA;

typedef struct _BDA_CAS_OPENMMIDATA {
  ULONG ulDialogNumber;
  ULONG ulDialogRequest;
  GUID uuidDialogType;
  USHORT usDialogDataLength;
  BYTE argbDialogData[MIN_DIMENSION];
} BDA_CAS_OPENMMIDATA, *PBDA_CAS_OPENMMIDATA;

typedef struct _BDA_CAS_CLOSEMMIDATA {
  ULONG ulDialogNumber;
} BDA_CAS_CLOSEMMIDATA, *PBDA_CAS_CLOSEMMIDATA;

#pragma pack(push, 1)
typedef struct _BDA_ISDBCAS_REQUESTHEADER {
  BYTE bInstruction;
  BYTE bReserved[3];
  ULONG ulDataLength;
  BYTE argbIsdbCommand[MIN_DIMENSION];
} BDA_ISDBCAS_REQUESTHEADER, *PBDA_ISDBCAS_REQUESTHEADER;

typedef struct _BDA_ISDBCAS_RESPONSEDATA {
  PBDARESULT lResult;
  ULONG ulRequestID;
  ULONG ulIsdbStatus;
  ULONG ulIsdbDataSize;
  BYTE argbIsdbCommandData[MIN_DIMENSION];
} BDA_ISDBCAS_RESPONSEDATA, *PBDA_ISDBCAS_RESPONSEDATA;

typedef struct _BDA_ISDBCAS_EMG_REQ {
  BYTE bCLA;
  BYTE bINS;
  BYTE bP1;
  BYTE bP2;
  BYTE bLC;
  BYTE bCardId[6];
  BYTE bProtocol;
  BYTE bCABroadcasterGroupId;
  BYTE bMessageControl;
  BYTE bMessageCode[MIN_DIMENSION];
} BDA_ISDBCAS_EMG_REQ, *PBDA_ISDBCAS_EMG_REQ;
#pragma pack(pop)

#pragma pack(push, 2)
typedef struct _BDA_MUX_PIDLISTITEM {
  USHORT usPIDNumber;
  USHORT usProgramNumber;
  MUX_PID_TYPE ePIDType;
} BDA_MUX_PIDLISTITEM, *PBDA_MUX_PIDLISTITEM;
#pragma pack(pop)

#pragma pack(push, 1)
typedef struct _BDA_TS_SELECTORINFO {
  BYTE bTSInfolength;
  BYTE bReserved[2];
  GUID guidNetworkType;
  BYTE bTSIDCount;
  USHORT usTSID[MIN_DIMENSION];
} BDA_TS_SELECTORINFO, *PBDA_TS_SELECTORINFO;

typedef struct _BDA_TS_SELECTORINFO_ISDBS_EXT {
  BYTE bTMCC[48];
} BDA_TS_SELECTORINFO_ISDBS_EXT, *PBDA_TS_SELECTORINFO_ISDBS_EXT;
#pragma pack(pop)

typedef struct _BDA_DVBT2_L1_SIGNALLING_DATA {
  BYTE L1Pre_TYPE;
  BYTE L1Pre_BWT_S1_S2;
  BYTE L1Pre_REPETITION_GUARD_PAPR;
  BYTE L1Pre_MOD_COD_FEC;
  BYTE L1Pre_POSTSIZE_INFO_PILOT[5];
  BYTE L1Pre_TX_ID_AVAIL;
  BYTE L1Pre_CELL_ID[2];
  BYTE L1Pre_NETWORK_ID[2];
  BYTE L1Pre_T2SYSTEM_ID[2];
  BYTE L1Pre_NUM_T2_FRAMES;
  BYTE L1Pre_NUM_DATA_REGENFLAG_L1POSTEXT[2];
  BYTE L1Pre_NUMRF_CURRENTRF_RESERVED[2];
  BYTE L1Pre_CRC32[4];
  BYTE L1PostData[MIN_DIMENSION];
} BDA_DVBT2_L1_SIGNALLING_DATA, *PBDA_DVBT2_L1_SIGNALLING_DATA;

typedef struct _BDA_RATING_PINRESET {
  BYTE bPinLength;
  BYTE argbNewPin[MIN_DIMENSION];
} BDA_RATING_PINRESET, *PBDA_RATING_PINRESET;

typedef struct _MPEG2_TRANSPORT_STRIDE {
  DWORD dwOffset;
  DWORD dwPacketLength;
  DWORD dwStride;
} MPEG2_TRANSPORT_STRIDE, *PMPEG2_TRANSPORT_STRIDE;

typedef struct _BDA_SIGNAL_TIMEOUTS {
  ULONG ulCarrierTimeoutMs;
  ULONG ulScanningTimeoutMs;
  ULONG ulTuningTimeoutMs;
} BDA_SIGNAL_TIMEOUTS, *PBDA_SIGNAL_TIMEOUTS;

#endif
#endif
