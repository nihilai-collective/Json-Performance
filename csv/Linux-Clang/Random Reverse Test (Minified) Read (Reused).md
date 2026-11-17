
----
### Random Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 953.014 | 0.140961 | 5911.26ms | 409725 | 30 | 1.00208e+07 | 410009 | 0.0735321 | 5.3872 | 25.8414 | 5.15295 | 0.0115654 | 0.00681172 | 4.40946e-05 | 1(Win) | true |
| simdjson (ondemand) | 484.161 | 0.209746 | 5442.83ms | 409725 | 30 | 8.59636e+07 | 807055 | 0.310745 | 10.5576 | 47.6373 | 8.62435 | 0.0350849 | 0.0135718 | 9.92536e-05 | 2(Loss) | true |
