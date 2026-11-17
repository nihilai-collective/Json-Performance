
----
### Apache Builds Small Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 964.484 | 0.322292 | 291.755ms | 2632 | 40 | 2814.1 | 2602.5 | 0.541401 | 2.50986 | 1(Win) | true |
| Jsonifier (two-stage) | 921.391 | 0.574993 | 279.078ms | 2632 | 1280 | 314065 | 2724.22 | 0.132093 | 2.65956 | 2(Loss) | true |
| Glaze | 806.683 | 0.29453 | 320.408ms | 2632 | 4890 | 410708 | 3111.6 | 0.240661 | 3.04 | 3(Loss) | true |
| simdjson (ondemand) | 640.197 | 0.519051 | 396.39ms | 2632 | 640 | 265060 | 3920.78 | 0.400889 | 3.83894 | 4(Loss) | true |
