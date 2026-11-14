
----
### Github Events Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2501.74 | 0.198859 | 101.424ms | 2158 | 4890 | 13086.3 | 822.638 | 0.0789114 | 1(Win) | true |
| Jsonifier (two-stage) | 2113.2 | 0.13624 | 122.796ms | 2158 | 4890 | 8608.79 | 973.893 | 0.017839 | 2(Loss) | true |
| Glaze | 1953.59 | 0.055808 | 122.292ms | 2158 | 2560 | 884.851 | 1053.46 | 0.162861 | 3(Loss) | true |
| simdjson (ondemand) | 1599.76 | 0.0860101 | 145.894ms | 2158 | 640 | 783.564 | 1286.46 | 0.389811 | 4(Loss) | true |
