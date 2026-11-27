
----
### Canada Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1862.99 | 0.0462917 | 1334.18ms | 11579 | 4890 | 36815.9 | 5927.35 | 0.0347022 | 2.74504 | 13.3812 | 2.3445 | 0.00136881 | 1.73786e-05 | 7.34706e-06 | 1(Win) | true |
| Jsonifier (generic) | 1744.29 | 0.0431457 | 1365.8ms | 11579 | 1280 | 9549.68 | 6330.71 | 0.148901 | 2.95707 | 13.2828 | 2.57898 | 0.00246904 | 2.13884e-05 | 8.29897e-06 | 2(Loss) | true |
