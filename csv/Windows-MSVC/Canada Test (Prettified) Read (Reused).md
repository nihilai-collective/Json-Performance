
----
### Canada Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1864.62 | 0.443452 | 10137.1ms | 5373214 | 80 | 1.18815e+10 | 2.74818e+06 | 0.113385 | 1.62982 | 1(Win) | true |
| Jsonifier | 1761.44 | 0.425625 | 5151.31ms | 5373214 | 80 | 1.22653e+10 | 2.90915e+06 | 0.0204139 | 1.72534 | 2(Loss) | true |
| simdjson (ondemand) | 1099.66 | 0.237148 | 7750.29ms | 5373214 | 40 | 4.88485e+09 | 4.65989e+06 | 0.144633 | 2.76365 | 3(Loss) | true |
| Glaze | 982.273 | 0.360748 | 8569.6ms | 5373214 | 40 | 1.41668e+10 | 5.21677e+06 | 0.414829 | 3.09389 | 4(Loss) | true |
