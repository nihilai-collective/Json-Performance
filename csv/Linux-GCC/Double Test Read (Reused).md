
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1491.94 | 0.0533297 | 121.899ms | 1811 | 80 | 30.4905 | 1157.62 | 0.0733723 | 1.6212 | 1(Win) | true |
| Glaze | 1064.01 | 0.0556709 | 167.022ms | 1811 | 80 | 65.3266 | 1623.2 | 0.0446449 | 2.28928 | 2(Loss) | true |
| simdjson (ondemand) | 390.097 | 0.212176 | 444.721ms | 1811 | 2560 | 225904 | 4427.37 | 0.117934 | 6.30668 | 3(Loss) | true |
| simdjson (reflection) | 371.871 | 0.242541 | 459.198ms | 1811 | 30 | 3806.65 | 4644.37 | 0.188396 | 6.61888 | 4(Loss) | true |
