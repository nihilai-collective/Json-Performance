
----
### Github Events Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1048.38 | 0.207243 | 5492.21ms | 53331 | 160 | 1.61735e+06 | 48513.5 | 0.187495 | 1(Win) | true |
| simdjson (ondemand) | 312.568 | 0.255502 | 8726.74ms | 53331 | 1280 | 2.21244e+08 | 162718 | 1.26264 | 2(Loss) | true |
