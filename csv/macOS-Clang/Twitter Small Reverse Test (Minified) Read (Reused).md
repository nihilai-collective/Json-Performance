
----
### Twitter Small Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 749.814 | 0.101339 | 378.714ms | 2821 | 80 | 1057.64 | 3587.97 | 0.0153266 | 1(Win) | true |
| simdjson (ondemand) | 185.089 | 0.277931 | 1391.36ms | 2821 | 2560 | 4.17792e+06 | 14535.2 | 0.495129 | 2(Loss) | true |
