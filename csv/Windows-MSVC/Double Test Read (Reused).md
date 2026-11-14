
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 579.079 | 0.265409 | 305.826ms | 1811 | 40 | 2506.41 | 2982.5 | 0.308296 | 5.20939 | 1(Win) | true |
| simdjson (ondemand) | 274.111 | 0.392109 | 629.044ms | 1811 | 2560 | 1.56256e+06 | 6300.74 | 0.144661 | 11.0387 | 2(Loss) | true |
