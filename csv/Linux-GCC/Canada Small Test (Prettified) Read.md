
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 1867.7 | 0.175167 | 1315.69ms | 11579 | 2560 | 274582 | 5912.4 | 0.0869626 | 2.76262 | 13.3566 | 2.33621 | 0.00167002 | 7.55004e-05 | 3.90659e-05 | 1(Win) | true |
| Jsonifier (generic) | 1627.76 | 0.0932376 | 1402.66ms | 11579 | 2560 | 102420 | 6783.92 | 0.118758 | 3.17549 | 13.5964 | 2.61232 | 0.00365796 | 3.00585e-05 | 1.06267e-05 | 2(Loss) | true |
