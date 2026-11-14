
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1574.13 | 0.0589734 | 850.5ms | 2158 | 640 | 380.464 | 1307.4 | 0.0735537 | 3.37295 | 11.9212 | 2.27016 | 0.000464116 | 6.29924e-05 | 1.95494e-05 | 1(Win) | true |
| simdjson (ondemand) | 1558.4 | 0.0569378 | 855.098ms | 2158 | 4890 | 2764.76 | 1320.61 | 0.30948 | 3.41347 | 11.9805 | 2.20158 | 0.00048007 | 0.000134279 | 7.17357e-05 | 2(Loss) | true |
