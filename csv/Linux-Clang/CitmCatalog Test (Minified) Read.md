
----
### CitmCatalog Test (Minified) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10735.5 | 0.0202708 | 5176ms | 500299 | 2560 | 207776 | 44443.2 | 0.0724575 | 0.478129 | 2.53347 | 0.124274 | 2.08336e-05 | 2.14403e-06 | 1.66853e-06 | 1(Win) | true |
| simdjson (stage-1) | 9526.75 | 0.0701441 | 5747.6ms | 500299 | 1280 | 1.57965e+06 | 50082.4 | 0.0105752 | 0.539744 | 2.57778 | 0.112553 | 2.15637e-05 | 7.01268e-05 | 6.48987e-06 | 2(Loss) | true |
