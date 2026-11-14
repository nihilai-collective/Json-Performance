
----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 13609.1 | 0.0545825 | 2014.19ms | 183677 | 160 | 7897.23 | 12871.3 | 0.0387824 | 0.379605 | 2.04089 | 0.0940401 | 2.34447e-05 | 3.47077e-06 | 2.24579e-06 | 1(Win) | true |
| simdjson (stage-1) | 12913.3 | 0.0370526 | 2080.57ms | 183677 | 640 | 16167.9 | 13565 | 0.0541889 | 0.399774 | 1.92758 | 0.0823348 | 2.66603e-05 | 1.74389e-06 | 1.01231e-06 | 2(Loss) | true |
