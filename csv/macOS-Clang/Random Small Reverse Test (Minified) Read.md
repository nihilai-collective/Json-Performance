
----
### Random Small Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Small%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 730.346 | 0.0804031 | 652.34ms | 4926 | 4890 | 130794 | 6432.29 | 0.0421508 | 1(Win) | true |
| simdjson (ondemand) | 337.807 | 0.3384 | 1403.5ms | 4926 | 640 | 1.41739e+06 | 13906.8 | 0.0340546 | 2(Loss) | true |
