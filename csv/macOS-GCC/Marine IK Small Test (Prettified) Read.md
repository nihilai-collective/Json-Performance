
----
### Marine IK Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1403.8 | 0.374833 | 1307.31ms | 18245 | 640 | 1.38145e+06 | 12394.8 | 0.145012 | 1(Win) | true |
| simdjson (ondemand) | 1195.35 | 0.262134 | 1497.68ms | 18245 | 1280 | 1.8636e+06 | 14556.2 | 0.172044 | 2(Loss) | true |
