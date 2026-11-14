
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 941.088 | 0.808477 | 260.671ms | 2632 | 2560 | 1.19038e+06 | 2667.2 | 1.63741 | 1(Win) | true |
| simdjson (ondemand) | 775.911 | 0.435142 | 330.979ms | 2632 | 1280 | 253642 | 3235 | 0.53499 | 2(Loss) | true |
