
----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 819.026 | 0.0434918 | 6177.91ms | 409725 | 640 | 2.75539e+07 | 477084 | 0.0545796 | 6.23636 | 28.8171 | 5.82669 | 0.0151376 | 0.0186543 | 6.82394e-05 | 1(Win) | true |
| simdjson (ondemand) | 446.361 | 0.108411 | 5595.04ms | 409725 | 80 | 7.20525e+07 | 875399 | 0.0845783 | 11.4466 | 50.6039 | 9.29602 | 0.0396665 | 0.0356322 | 1.10135e-05 | 2(Loss) | true |
