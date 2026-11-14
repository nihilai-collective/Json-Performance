
----
### Github Events Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 647.032 | 0.908052 | 244.655ms | 1691 | 640 | 327821 | 2492.4 | 0.906489 | 1(Win) | true |
| simdjson (ondemand) | 561.2 | 2.05459 | 332.8ms | 1691 | 40 | 139432 | 2873.6 | 0.223214 | 2(Loss) | true |
