
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 854.001 | 0.552923 | 196.368ms | 1691 | 2560 | 279087 | 1888.36 | 1.05932 | 1(Win) | true |
| simdjson (ondemand) | 624.217 | 0.364411 | 238.156ms | 1691 | 2560 | 226902 | 2583.5 | 0.393261 | 2(Loss) | true |
