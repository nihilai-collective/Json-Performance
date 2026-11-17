
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2179.98 | 0.164493 | 351.601ms | 7932 | 640 | 20851.3 | 3470 | 0.18044 | 1.38756 | 1(Win) | true |
| Jsonifier | 1971.99 | 0.0945823 | 386.453ms | 7932 | 4890 | 64370.1 | 3835.99 | 0.0911108 | 1.53295 | 2(Loss) | true |
| Glaze | 1617.04 | 0.092488 | 470.747ms | 7932 | 2560 | 47921.8 | 4678.01 | 0.0208712 | 1.87148 | 3(Loss) | true |
| simdjson (ondemand) | 1304.51 | 0.104005 | 580.19ms | 7932 | 80 | 2909.81 | 5798.75 | 0.0215517 | 2.32225 | 4(Loss) | true |
