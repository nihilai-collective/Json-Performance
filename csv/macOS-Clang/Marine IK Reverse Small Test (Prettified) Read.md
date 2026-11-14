
----
### Marine IK Reverse Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Reverse%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1903.35 | 0.0560215 | 932.226ms | 18245 | 40 | 1049.11 | 9141.65 | 0.0154944 | 1(Win) | true |
| Jsonifier | 1890.42 | 0.0642053 | 949.441ms | 18245 | 80 | 2793.84 | 9204.17 | 0.0445252 | 2(Loss) | true |
| Glaze | 1215.38 | 0.150787 | 1442.54ms | 18245 | 640 | 298246 | 14316.4 | 0.198473 | 3(Loss) | true |
| simdjson (ondemand) | 1207.13 | 0.0970316 | 1500.09ms | 18245 | 4890 | 956561 | 14414.1 | 0.130857 | 4(Loss) | true |
