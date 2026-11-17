
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2016.75 | 0.139787 | 473.226ms | 8051 | 4890 | 138496 | 3807.13 | 0.213362 | 1(Win) | true |
| Jsonifier (two-stage) | 1575.24 | 0.435652 | 657.301ms | 8051 | 2560 | 1.15432e+06 | 4874.2 | 0.756443 | 2(Loss) | true |
| Glaze | 1528.43 | 0.291087 | 640.571ms | 8051 | 30 | 6414.67 | 5023.47 | 0.163501 | 3(Loss) | true |
| simdjson (ondemand) | 1070.11 | 1.27865 | 803.319ms | 8051 | 160 | 1.34668e+06 | 7174.98 | 0.383196 | 4(Loss) | true |
