
----
### Marine IK Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1352.9 | 0.058872 | 1303.29ms | 18245 | 30 | 1719.86 | 12861.1 | 0.0318893 | 1(Win) | true |
| simdjson (ondemand) | 1257.81 | 0.0662951 | 1416.68ms | 18245 | 30 | 2523.14 | 13833.4 | 0.0496137 | 2(Loss) | true |
