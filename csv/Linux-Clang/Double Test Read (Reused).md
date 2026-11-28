
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1395.98 | 0.0845866 | 126.939ms | 1811 | 30 | 32.8552 | 1237.2 | 0.0565474 | 1.73379 | 1(Win) | true |
| Glaze | 947.882 | 0.0681602 | 191.976ms | 1811 | 30 | 46.2713 | 1822.07 | 0.0347712 | 2.57315 | 2(Loss) | true |
| simdjson (ondemand) | 407.373 | 0.0550653 | 433.26ms | 1811 | 80 | 436.013 | 4239.61 | 0.0469013 | 6.04161 | 3(Loss) | true |
