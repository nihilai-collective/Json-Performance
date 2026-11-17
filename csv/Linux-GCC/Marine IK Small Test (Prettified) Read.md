
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2035.18 | 0.0972183 | 1611.96ms | 18245 | 80 | 5526.73 | 8549.51 | 0.0799114 | 2.54336 | 10.3289 | 2.00543 | 0.00245204 | 7.53631e-06 | 2.05536e-06 | 1(Win) | true |
| simdjson (ondemand) | 1983.74 | 0.0364437 | 1614.81ms | 18245 | 4890 | 49965.8 | 8771.21 | 0.812179 | 2.57957 | 10.7568 | 1.91981 | 0.00302159 | 2.84135e-05 | 1.39994e-05 | 2(Loss) | true |
