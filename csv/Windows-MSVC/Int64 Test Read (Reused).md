
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1963.01 | 0.25518 | 195.15ms | 3862 | 80 | 1833.86 | 1876.25 | 0.334225 | 1.2377 | 1(Win) | true |
| Jsonifier (two-stage) | 1790.81 | 0.447416 | 208.681ms | 3862 | 30 | 2540.23 | 2056.67 | 0.162338 | 1.36394 | 2(Loss) | true |
| Glaze | 1097.79 | 0.18291 | 346.846ms | 3862 | 80 | 3012.66 | 3355 | 0.0744602 | 2.24014 | 3(Loss) | true |
| simdjson (ondemand) | 711.193 | 0.177475 | 582.562ms | 3862 | 80 | 6757.91 | 5178.75 | 0.0724638 | 3.46094 | 4(Loss) | true |
