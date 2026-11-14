
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1467.01 | 0.17159 | 7123.27ms | 7351818 | 80 | 5.3802e+09 | 4.77928e+06 | 2.86042 | 1(Win) | true |
| simdjson (ondemand) | 1206.37 | 1.26292 | 8163.25ms | 7351818 | 30 | 1.61623e+11 | 5.81186e+06 | 3.75202 | 2(Loss) | true |
