
----
### Canada Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 472.417 | 0.153424 | 1114.64ms | 4630 | 1280 | 263213 | 9346.65 | 0.0672249 | 1(Win) | true |
| simdjson (ondemand) | 452.358 | 0.057309 | 1104.19ms | 4630 | 30 | 938.783 | 9761.1 | 0.0290184 | 2(Loss) | true |
