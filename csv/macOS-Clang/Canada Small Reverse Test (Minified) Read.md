
----
### Canada Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 454.297 | 0.0871679 | 988.804ms | 4630 | 30 | 2153.36 | 9719.43 | 0.0150923 | 1(Win) | true |
| simdjson (ondemand) | 418.782 | 0.0614591 | 1066.81ms | 4630 | 40 | 1679.65 | 10543.7 | 0.00600711 | 2(Loss) | true |
