#pragma once

#include <map>
#include <string>
#include <cstdint>

#include <amd_smi/impl/amd_smi_system.h>

struct NICData {
    std::string name; // RDMA device name
    std::string netdev; // NIC name
    uint32_t num_stats {}; // Number of stats collected for this NIC

    std::uint32_t rx_rdma_ucast_bytes {}; // unicast received bytes
    std::uint32_t rx_rdma_ucast_pkts {};  // unicast received packets
    std::uint32_t tx_rdma_ucast_bytes {}; // unicast transmitted bytes
    std::uint32_t tx_rdma_ucast_pkts {};  // unicast transmitted packets

    std::uint32_t rx_rdma_cnp_pkts {}; // received CNP packets
    std::uint32_t tx_rdma_cnp_pkts {}; // transmitted CNP packets

    std::string to_string() const;

    static const char* RX_RDMA_UCAST_BYTES;
    static const char* RX_RDMA_UCAST_PKTS;
    static const char* TX_RDMA_UCAST_BYTES;
    static const char* TX_RDMA_UCAST_PKTS;

    static const char* RX_RDMA_CNP_PKTS;
    static const char* TX_RDMA_CNP_PKTS;
};

using nic_params_t = std::map<std::string, NICData>;

class AINICStatsCollector {
private:
    amd::smi::AMDSmiSystem& _amdsmi; // Reference to the singleton instance of AMDSmiSystem
    nic_params_t _nic_params; // Mapping NIC name -> NIC statistics

    // Return reference to data associated with the specified NIC.
    // If the data for nic don't exist yet, create them.
    NICData& get_data(const std::string& nic);
public:
    AINICStatsCollector();
    void get_stats();

    const nic_params_t& params();
};
