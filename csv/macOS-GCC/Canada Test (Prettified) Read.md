
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1421.51 | 0.66924 | 5319.2ms | 5373214 | 30 | 1.74604e+10 | 3.60483e+06 | 0.275351 | 1(Win) | true |
| Glaze | 1277.75 | 0.108485 | 6063.8ms | 5373214 | 30 | 5.67856e+08 | 4.0104e+06 | 0.214943 | 2(Loss) | true |
| Jsonifier (two-stage) | 1258.79 | 0.402699 | 6211.46ms | 5373214 | 40 | 1.07493e+10 | 4.0708e+06 | 0.00953876 | 3(Loss) | true |
| simdjson (reflection) | 1225.69 | 0.846468 | 6132.23ms | 5373214 | 30 | 3.75705e+10 | 4.18073e+06 | 3.03167 | 4(Loss) | true |
| simdjson (ondemand) | 1069.12 | 1.28598 | 7022.12ms | 5373214 | 40 | 1.51964e+11 | 4.79299e+06 | 0.813974 | 5(Loss) | true |
