
----
### Random Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1648.38 | 0.104727 | 478.666ms | 8150 | 30 | 731.545 | 4715.2 | 0.263673 | 1(Win) | true |
| simdjson (ondemand) | 1289.81 | 0.0846266 | 612.641ms | 8150 | 40 | 1040.25 | 6026.05 | 0.0401198 | 2(Loss) | true |
