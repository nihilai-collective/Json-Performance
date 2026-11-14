
----
### Int64 Test Read (Reused) Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1993.55 | 0.432822 | 191.426ms | 3862 | 40 | 2557.69 | 1847.5 | 0.0451264 | 1.49957 | 1(Win) | true |
| Glaze | 1117.22 | 0.101112 | 338.085ms | 3862 | 30 | 333.333 | 3296.67 | 0.202634 | 2.69396 | 2(Loss) | true |
| Jsonifier (two-stage) | 988.828 | 0.077142 | 379.879ms | 3862 | 4890 | 40371.4 | 3724.7 | 0.293404 | 3.04976 | 3(Loss) | true |
| simdjson (ondemand) | 462.918 | 0.0701501 | 788.849ms | 3862 | 80 | 2492.09 | 7956.25 | 0.489422 | 6.54362 | 4(Loss) | true |
