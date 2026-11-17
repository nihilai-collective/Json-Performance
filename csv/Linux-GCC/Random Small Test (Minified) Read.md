
----
### Random Small Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Random%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1339.83 | 0.0714967 | 1074.57ms | 4926 | 640 | 4022.01 | 3506.27 | 0.0624718 | 3.88715 | 16.5483 | 3.17519 | 0.00458219 | 3.23538e-05 | 1.90317e-06 | 1(Win) | true |
| simdjson (ondemand) | 1085.84 | 0.0607064 | 1154.86ms | 4926 | 4890 | 33731.2 | 4326.4 | 0.129102 | 4.78207 | 18.447 | 3.43017 | 0.00348508 | 4.74923e-05 | 1.61075e-05 | 2(Loss) | true |
