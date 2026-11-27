
----
### Github Events Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 928.74 | 0.775498 | 178.062ms | 1691 | 1280 | 232098 | 1736.4 | 0.57924 | 1(Win) | true |
| simdjson (ondemand) | 769.694 | 0.589587 | 212.778ms | 1691 | 640 | 97662.4 | 2095.2 | 0.692042 | 2(Loss) | true |
