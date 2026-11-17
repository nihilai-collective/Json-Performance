
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1442.92 | 0.391581 | 7292.9ms | 7351818 | 30 | 1.0861e+10 | 4.85906e+06 | 1.28282 | 1.71582 | 1(Win) | true |
| simdjson (ondemand) | 878.168 | 0.106642 | 5699.9ms | 7351818 | 30 | 2.17478e+09 | 7.98394e+06 | 1.7406 | 2.81926 | 2(Loss) | true |
