
----
### Random Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 539.964 | 0.118673 | 9205.97ms | 409725 | 320 | 2.35998e+08 | 723649 | 0.0377717 | 5.62857 | 1(Win) | true |
| simdjson (ondemand) | 335.375 | 0.217047 | 7425.12ms | 409725 | 40 | 2.55796e+08 | 1.1651e+06 | 0.00236037 | 9.0623 | 2(Loss) | true |
