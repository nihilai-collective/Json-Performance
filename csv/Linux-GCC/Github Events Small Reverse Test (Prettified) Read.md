
----
### Github Events Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1077.75 | 0.0584483 | 911.757ms | 2158 | 320 | 398.618 | 1909.55 | 0.00212751 | 4.88063 | 17.1835 | 3.46154 | 0.00182316 | 8.10936e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 926.107 | 0.0341917 | 941.246ms | 2158 | 4890 | 2823.13 | 2222.24 | 0.0760224 | 5.65997 | 21.9078 | 4.24004 | 0.00184902 | 5.31622e-05 | 5.87532e-06 | 2(Loss) | true |
