
----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1364.22 | 0.0931256 | 6670.36ms | 94653 | 1280 | 4.86012e+06 | 66168.2 | 0.0391426 | 1.81407 | 1(Win) | true |
| simdjson (ondemand) | 1301.52 | 0.0614173 | 6983.92ms | 94653 | 1280 | 2.32253e+06 | 69356.1 | 0.220469 | 1.90153 | 2(Loss) | true |
