
----
### Marine IK Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 2346.43 | 0.144675 | 10076.3ms | 7351818 | 80 | 1.49504e+09 | 2.98805e+06 | 1.26164 | 2.17064 | 8.98884 | 1.44299 | 0.0108085 | 0.0533853 | 0.00130546 | 1(Win) | true |
| Jsonifier (generic) | 2301.96 | 0.124383 | 10174.5ms | 7351818 | 160 | 2.29634e+09 | 3.04577e+06 | 0.0937409 | 2.21075 | 8.7135 | 1.6566 | 0.010221 | 0.0535192 | 0.00102076 | 2(Loss) | true |
