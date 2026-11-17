
----
### Double Test Read Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 435.557 | 0.286923 | 402.294ms | 1811 | 1280 | 165687 | 3965.28 | 0.0966643 | 5.64753 | 1(Win) | true |
| simdjson (ondemand) | 261.276 | 0.0501473 | 661.907ms | 1811 | 30 | 329.651 | 6610.27 | 0.156061 | 9.43849 | 2(Loss) | true |
