
----
### Instruments Small Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 506.585 | 0.0758981 | 886.22ms | 4669 | 40 | 1780.18 | 8789.65 | 0.0400252 | 1(Win) | true |
| simdjson (ondemand) | 148.749 | 0.0772184 | 3057.05ms | 4669 | 4890 | 2.61272e+06 | 29934.4 | 0.158133 | 2(Loss) | true |
