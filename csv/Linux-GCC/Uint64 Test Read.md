
----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 4707.95 | 0.0410071 | 785.341ms | 3873 | 320 | 33.1206 | 784.541 | 0.0833187 | 1.15355 | 6.62845 | 0.58172 | 0.000774593 | 2.33992e-05 | 3.22747e-06 | 1(Win) | true |
| simdjson (stage-1) | 1474.64 | 0.0443425 | 959.992ms | 3873 | 2560 | 3157.95 | 2504.74 | 0.0710565 | 3.5398 | 17.875 | 1.35425 | 0.000661228 | 3.59056e-05 | 4.03434e-07 | 2(Loss) | true |
