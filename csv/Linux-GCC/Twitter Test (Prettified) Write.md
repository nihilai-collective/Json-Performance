
----
### Twitter Test (Prettified) Write Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 20969.8 | 0.0850593 | 4110.38ms | 716365 | 160 | 122870 | 32579.2 | 0.0972614 | 0.241474 | 0.716025 | 0.0983605 | 0.000184421 | 0.0076338 | 8.65481e-06 | 1(Win) | true |
| Glaze | 5078.95 | 0.473088 | 7325.3ms | 716365 | 1280 | 5.1834e+08 | 134512 | 0.305923 | 0.998999 | 2.70614 | 0.438118 | 0.000371069 | 0.0489601 | 6.66265e-05 | 2(Loss) | true |
| simdjson (reflection) | 515.275 | 0.378238 | 8467.05ms | 716365 | 160 | 4.02384e+09 | 1.32585e+06 | 0.0507152 | 9.7576 | 30.5979 | 6.83611 | 0.0701478 | 0.288981 | 0.000873882 | 3(Loss) | true |
