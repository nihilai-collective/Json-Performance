
----
### Marine IK Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1546.19 | 0.0435557 | 6866.67ms | 7351818 | 80 | 3.12067e+08 | 4.53454e+06 | 0.020945 | 1(Win) | true |
| simdjson (ondemand) | 1445.12 | 0.0751126 | 7497.36ms | 7351818 | 30 | 3.98409e+08 | 4.85167e+06 | 0.120151 | 2(Loss) | true |
