
----
### Github Events Small Test (Prettified) Write Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11096.2 | 0.385033 | 743.457ms | 2866 | 4890 | 4398.57 | 246.322 | 0.0570472 | 0.536932 | 1.13643 | 0.187369 | 0.000349275 | 3.38929e-05 | 1.1916e-05 | 1(Win) | true |
| Glaze | 3807.25 | 0.205368 | 795.658ms | 2866 | 1280 | 2782.3 | 717.902 | 0.0400633 | 1.42389 | 4.01605 | 0.668179 | 0.000352189 | 5.6154e-05 | 2.67141e-05 | 2(Loss) | true |
| simdjson (reflection) | 547.233 | 0.0963221 | 1228.83ms | 2866 | 2560 | 59251.7 | 4994.64 | 0.238094 | 9.3694 | 34.918 | 7.32764 | 0.00882164 | 0.000187544 | 0.000105084 | 3(Loss) | true |
