
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1150.86 | 0.330322 | 1608.54ms | 18245 | 1280 | 3.19249e+06 | 15119 | 0.0194048 | 1(Win) | true |
| simdjson (ondemand) | 991.706 | 0.191233 | 1636.98ms | 18245 | 4890 | 5.50501e+06 | 17545.3 | 0.731956 | 2(Loss) | true |
