
----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10777.1 | 0.0259873 | 5144.11ms | 500299 | 640 | 84715.5 | 44272 | 0.0226848 | 0.477998 | 2.53347 | 0.124274 | 2.16402e-05 | 4.185e-07 | 1.24925e-08 | 1(Win) | true |
| simdjson (stage-1) | 9575.93 | 0.040741 | 5720.32ms | 500299 | 160 | 65929.7 | 49825.2 | 0.0411019 | 0.538064 | 2.57778 | 0.112553 | 2.04128e-05 | 2.12373e-06 | 1.64901e-06 | 2(Loss) | true |
