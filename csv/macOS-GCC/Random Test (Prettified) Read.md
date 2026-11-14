
----
### Random Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1426.2 | 0.137957 | 6371.12ms | 676745 | 80 | 3.11795e+07 | 452528 | 0.526856 | 1(Win) | true |
| simdjson (ondemand) | 893.573 | 0.467604 | 5036.99ms | 676745 | 80 | 9.12507e+08 | 722262 | 1.2923 | 2(Loss) | true |
