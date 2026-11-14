
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1362.35 | 0.0407395 | 1028.17ms | 4390 | 2560 | 4012.54 | 3073.08 | 0.0227709 | 3.82826 | 17.6116 | 3.28907 | 0.00117063 | 3.56812e-05 | 3.2033e-06 | 1(Win) | true |
| simdjson (ondemand) | 1055.21 | 0.0358799 | 1112.48ms | 4390 | 2560 | 5187.91 | 3967.57 | 0.0423175 | 4.92792 | 19.5522 | 3.61526 | 0.00292924 | 3.70159e-05 | 8.18622e-06 | 2(Loss) | true |
