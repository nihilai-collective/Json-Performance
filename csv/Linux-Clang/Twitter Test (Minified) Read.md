
----
### Twitter Test (Minified) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 24598.3 | 0.173666 | 1816.34ms | 466906 | 1280 | 1.265e+06 | 18101.9 | 0.284941 | 0.100506 | 1(Win) | true |
| simdjson (stage-1) | 21161 | 0.118906 | 2115.73ms | 466906 | 1280 | 801322 | 21042.3 | 0.00950003 | 0.116857 | 2(Loss) | true |
