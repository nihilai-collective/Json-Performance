
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1416.66 | 0.157481 | 9083.99ms | 264040 | 1280 | 1.00294e+08 | 177748 | 0.105594 | 1(Win) | true |
| simdjson (ondemand) | 1286.61 | 0.17409 | 10141.9ms | 264040 | 640 | 7.42972e+07 | 195714 | 0.0384868 | 2(Loss) | true |
