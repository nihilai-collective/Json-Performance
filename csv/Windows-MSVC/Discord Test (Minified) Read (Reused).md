
----
### Discord Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1776.09 | 0.0490487 | 3523.1ms | 56369 | 1280 | 282107 | 30267.3 | 0.057269 | 1.71014 | 1(Win) | true |
| Glaze | 1626.52 | 0.14944 | 3730.16ms | 56369 | 160 | 390314 | 33050.6 | 0.0662302 | 1.86729 | 2(Loss) | true |
| Jsonifier (two-stage) | 1350.92 | 0.0478122 | 4467.26ms | 56369 | 1280 | 463348 | 39793.3 | 0.062471 | 2.24851 | 3(Loss) | true |
| simdjson (ondemand) | 900.805 | 0.0885536 | 6411.39ms | 56369 | 640 | 1.78736e+06 | 59677.3 | 0.102269 | 3.37261 | 4(Loss) | true |
