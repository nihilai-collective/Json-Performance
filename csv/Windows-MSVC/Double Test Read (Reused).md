
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1405.76 | 0.145494 | 126.681ms | 1811 | 640 | 2044.97 | 1228.59 | 0.114329 | 1.72393 | 1(Win) | true |
| Glaze | 510.789 | 0.0915454 | 344.543ms | 1811 | 160 | 1533.02 | 3381.25 | 0.0738825 | 4.80754 | 2(Loss) | true |
| Jsonifier (two-stage) | 418.861 | 0.190478 | 419.196ms | 1811 | 30 | 1850.57 | 4123.33 | 0.0807754 | 5.879 | 3(Loss) | true |
| simdjson (ondemand) | 146.453 | 0.188839 | 1192.93ms | 1811 | 1280 | 634797 | 11792.9 | 0.18581 | 16.8653 | 4(Loss) | true |
