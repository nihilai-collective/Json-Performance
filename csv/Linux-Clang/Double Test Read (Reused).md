
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1401.31 | 0.0371799 | 127.467ms | 1811 | 160 | 33.5974 | 1232.49 | 0.219094 | 1.72836 | 1(Win) | true |
| Glaze | 883.61 | 0.0555376 | 200.952ms | 1811 | 30 | 35.3517 | 1954.6 | 0.242752 | 2.7617 | 2(Loss) | true |
| simdjson (ondemand) | 436.799 | 0.120204 | 403.163ms | 1811 | 40 | 903.59 | 3954 | 0.151976 | 5.6296 | 3(Loss) | true |
