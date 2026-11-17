
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 449.855 | 0.0435821 | 391.806ms | 1811 | 40 | 111.987 | 3839.25 | 0.08198 | 5.46945 | 1(Win) | true |
| simdjson (ondemand) | 267.397 | 0.169322 | 649.925ms | 1811 | 2560 | 306188 | 6458.94 | 0.0647906 | 9.22265 | 2(Loss) | true |
