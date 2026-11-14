
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 752.265 | 1.02864 | 575.704ms | 3862 | 40 | 101455 | 4896 | 1.41753 | 1(Win) | true |
| simdjson (ondemand) | 411.284 | 0.472685 | 878.414ms | 3862 | 2560 | 4.58696e+06 | 8955.1 | 1.15784 | 2(Loss) | true |
