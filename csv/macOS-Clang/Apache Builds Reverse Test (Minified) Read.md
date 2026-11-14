
----
### Apache Builds Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 891.056 | 0.177045 | 5915.46ms | 94653 | 160 | 5.14688e+06 | 101305 | 0.256884 | 1(Win) | true |
| simdjson (ondemand) | 430.565 | 0.333718 | 5195.08ms | 94653 | 640 | 3.13278e+08 | 209650 | 1.67184 | 2(Loss) | true |
