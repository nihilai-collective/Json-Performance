
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2309.54 | 0.299712 | 9405.69ms | 7351818 | 30 | 2.48353e+09 | 3.03578e+06 | 0.156964 | 1.07198 | 1(Win) | true |
| simdjson (ondemand) | 2270.04 | 0.120512 | 9853.05ms | 7351818 | 40 | 5.54169e+08 | 3.0886e+06 | 0.512762 | 1.09064 | 2(Loss) | true |
