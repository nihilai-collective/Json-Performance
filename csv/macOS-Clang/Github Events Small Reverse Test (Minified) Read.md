
----
### Github Events Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 728.649 | 0.275024 | 224.069ms | 1691 | 4890 | 181176 | 2213.22 | 0.0529524 | 1(Win) | true |
| simdjson (ondemand) | 454.844 | 0.215331 | 367.818ms | 1691 | 160 | 9326.04 | 3545.53 | 0.738922 | 2(Loss) | true |
