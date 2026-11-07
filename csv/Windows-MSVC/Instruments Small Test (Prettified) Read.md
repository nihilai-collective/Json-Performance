
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1852.92 | 0.104714 | 435.695ms | 7932 | 80 | 1462.03 | 4082.5 | 0.0612745 | 1.3258 | 1(Win) | true |
| Jsonifier | 1644.47 | 0.13482 | 473.509ms | 7932 | 40 | 1538.46 | 4600 | 0.0724113 | 1.49576 | 2(Loss) | true |
| Glaze | 1321.34 | 0.444273 | 585.042ms | 7932 | 1280 | 828034 | 5724.92 | 0.00136467 | 1.8641 | 3(Loss) | true |
| simdjson (ondemand) | 1199.45 | 0.16886 | 648.148ms | 7932 | 30 | 3402.3 | 6306.67 | 0 | 2.05706 | 4(Loss) | true |
