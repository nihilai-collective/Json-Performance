
----
### Apache Builds Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14267.2 | 0.0946676 | 750.364ms | 3643 | 2560 | 136.044 | 243.511 | 0.229113 | 0.413796 | 1.30387 | 0.214658 | 0.000274928 | 2.76644e-05 | 1.1366e-05 | 1(Win) | true |
| Glaze | 4211.13 | 0.0917283 | 814.501ms | 3682 | 4890 | 2860.79 | 833.845 | 0.0793125 | 1.25886 | 4.2208 | 0.702879 | 0.000274813 | 3.61567e-05 | 1.08859e-05 | 2(Loss) | true |
| simdjson (reflection) | 544.768 | 0.15796 | 1382.57ms | 3643 | 640 | 64948.1 | 6377.45 | 0.0570939 | 9.29255 | 36.0878 | 7.56163 | 0.0156241 | 0.000106797 | 4.58928e-05 | 3(Loss) | true |
