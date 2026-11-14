
----
### Random Test (Prettified) Write Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 21490.3 | 0.0937656 | 4546.87ms | 837491 | 640 | 777221 | 37165.4 | 0.121093 | 0.237635 | 0.835238 | 0.124859 | 0.000139766 | 0.00599574 | 2.57391e-05 | 1(Win) | true |
| Glaze | 4844.08 | 0.397708 | 8980.1ms | 837491 | 1280 | 5.50397e+08 | 164880 | 1.60093 | 1.03818 | 4.43688 | 0.73033 | 0.00588968 | 0.0492155 | 0.000138031 | 2(Loss) | true |
| simdjson (reflection) | 525.004 | 1.26263 | 9677.28ms | 837491 | 160 | 5.90343e+10 | 1.52131e+06 | 0.0504923 | 9.66806 | 37.3301 | 7.15622 | 0.0245811 | 0.329959 | 0.00142833 | 3(Loss) | true |
