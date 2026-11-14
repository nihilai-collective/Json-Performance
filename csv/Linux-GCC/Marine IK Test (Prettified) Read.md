
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2294.35 | 0.187108 | 9716.42ms | 7351818 | 30 | 9.80788e+08 | 3.05587e+06 | 0.86299 | 1.07908 | 1(Win) | true |
| simdjson (ondemand) | 2237.82 | 0.0995501 | 9894.78ms | 7351818 | 30 | 2.9184e+08 | 3.13307e+06 | 0.31208 | 1.10628 | 2(Loss) | true |
