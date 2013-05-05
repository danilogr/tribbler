# RPC Interface between Tribble server and backend KV store.
# Malveeka Tewari (malveeka@cs.ucsd.edu)
# Modified by Danilo (danilod100@gmail.com)
# (this is a specific solution, meaning that
# for a wide synchronized solution I would add
# a timestamp for all Put,Add and Delete functions)
# Include timestamp as part of functions KVPut
# Include timestamp as return from GetResponse

namespace cpp KeyValueStore

/**
 * Enum type for returning status of a RPC request made to the
 * the storage server.
 */

enum KVStoreStatus {
    OK = 1,
    EKEYNOTFOUND = 2,
    EITEMNOTFOUND = 3, // item not found in lists
    EPUTFAILED = 4,
    EITEMEXISTS = 5, // duplicate in lists
    INTERNAL_FAILURE = 6,
    NOT_IMPLEMENTED = 7
}

/**
 * Return type for a Get(key) RPC call to the storage server.
 */

struct GetResponse {
    1: KVStoreStatus status,
    2: string value
    3: list<i64> timestamp
}

/**
 * Return type for a GetList(key) RPC call to the storage server.
 */

struct GetListResponse {
    1: KVStoreStatus status,
    2: list<string> values,
}

/**
 * RPC services offered by the backed KeyValues store.
 */

service KeyValueStore {
    GetResponse Get(1:string key),
    GetListResponse GetList(1:string key),
    KVStoreStatus Put(1:string key, 2:string value, 3:string clientid),
    KVStoreStatus AddToList(1:string key, 2:string value, 3:string clientid),
    KVStoreStatus RemoveFromList(1:string key, 2:string value, 3:string clientid),

    oneway void KVPut(1:string key, 2:string value, 3:string clientid, 4:list<i64> timestamp),
    oneway void KVAddToList(1:string key, 2:string value, 3:string clientid),
    oneway void KVRemoveFromList(1:string key, 2:string value, 3:string clientid)
}
