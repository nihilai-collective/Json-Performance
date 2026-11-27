
----
### Instruments Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2163.52 | 0.0453115 | 8571.21ms | 183677 | 30 | 40376.2 | 80964.3 | 0.147337 | 1(Win) | true |
| simdjson (ondemand) | 1854.96 | 0.255567 | 9569.95ms | 183677 | 80 | 4.65949e+06 | 94432 | 0.297317 | 2(Loss) | true |
