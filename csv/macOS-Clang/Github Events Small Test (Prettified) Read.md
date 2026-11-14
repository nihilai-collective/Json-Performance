
----
### Github Events Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1092.68 | 0.167208 | 194.803ms | 2158 | 1280 | 12695.3 | 1883.47 | 0.344497 | 1(Win) | true |
| simdjson (ondemand) | 978.546 | 0.39548 | 219.33ms | 2158 | 40 | 2767.26 | 2103.15 | 0.0483168 | 2(Loss) | true |
