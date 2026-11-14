
----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4236.65 | 0.114515 | 794.347ms | 3873 | 1280 | 1275.8 | 871.816 | 0.00412197 | 1.27227 | 6.62845 | 0.58172 | 0.000755229 | 4.84121e-05 | 1.02876e-05 | 1(Win) | true |
| simdjson (stage-1) | 1502.15 | 0.160272 | 954.671ms | 3873 | 30 | 465.913 | 2458.87 | 0.0596125 | 3.54778 | 17.875 | 1.35425 | 0.000860659 | 1.72132e-05 | 0 | 2(Loss) | true |
