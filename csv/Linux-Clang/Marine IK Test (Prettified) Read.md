
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2241.7 | 0.352769 | 9766.74ms | 7351818 | 40 | 4.86939e+09 | 3.12764e+06 | 0.48559 | 1.1044 | 1(Win) | true |
| simdjson (ondemand) | 2066.05 | 0.205408 | 5089.6ms | 7351818 | 80 | 3.88716e+09 | 3.39354e+06 | 0.643622 | 1.19823 | 2(Loss) | true |
