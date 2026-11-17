
----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7758.41 | 0.0923983 | 948.487ms | 18245 | 1280 | 5496.43 | 2242.7 | 0.0795573 | 0.670858 | 3.22077 | 0.452234 | 0.000439718 | 1.66141e-05 | 8.26425e-06 | 1(Win) | true |
| simdjson (ondemand) | 5760.25 | 0.0820906 | 1024.12ms | 18245 | 1280 | 7870.48 | 3020.66 | 0.188512 | 0.90249 | 4.39682 | 0.635955 | 0.000339434 | 6.16607e-06 | 4.71019e-07 | 2(Loss) | true |
