
----
### Apache Builds Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3743.88 | 0.135805 | 797.923ms | 3370 | 1280 | 1739.62 | 858.435 | 0.0244753 | 1.43718 | 5.77745 | 0.982197 | 0.00104228 | 3.77875e-05 | 1.62277e-06 | 1(Win) | true |
| simdjson (ondemand) | 3111.92 | 0.0690902 | 816.705ms | 3370 | 1280 | 651.697 | 1032.76 | 0.0610094 | 1.72031 | 6.49703 | 1.02641 | 0.00230295 | 1.62277e-05 | 9.273e-07 | 2(Loss) | true |
