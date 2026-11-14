
----
### Instruments Small Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Instruments%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1550.24 | 0.118286 | 1007.08ms | 4669 | 320 | 3693.72 | 2872.27 | 0.0508349 | 3.36619 | 13.7333 | 2.7644 | 0.00163847 | 3.6812e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 1495.81 | 0.0383169 | 1018.03ms | 4669 | 4890 | 6361.88 | 2976.79 | 0.0197338 | 3.48603 | 15.2215 | 2.50375 | 0.00106993 | 3.89814e-05 | 1.10812e-05 | 2(Loss) | true |
