
----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10243.7 | 0.101233 | 889.104ms | 18245 | 4890 | 14458.7 | 1698.59 | 0.0539883 | 0.513392 | 2.44423 | 0.258537 | 0.000110135 | 1.06144e-05 | 2.53312e-06 | 1(Win) | true |
| simdjson (ondemand) | 9752.37 | 0.0461618 | 896.006ms | 18245 | 1280 | 868.247 | 1784.16 | 0.00678762 | 0.540241 | 2.78219 | 0.279255 | 0.000146144 | 8.26425e-06 | 1.24178e-06 | 2(Loss) | true |
