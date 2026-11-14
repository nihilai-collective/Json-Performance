
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 762 | 0.12393 | 1316.24ms | 4630 | 1280 | 66010.5 | 5794.64 | 0.16373 | 6.67317 | 32.2382 | 5.70446 | 0.00328817 | 9.61798e-05 | 5.41644e-05 | 1(Win) | true |
| Jsonifier (generic) | 723.512 | 0.0733727 | 1344.47ms | 4630 | 1280 | 25665.5 | 6102.89 | 0.0108439 | 7.02574 | 33.0283 | 6.3946 | 0.00335296 | 0.000103604 | 6.10826e-05 | 2(Loss) | true |
