
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1379.44 | 0.496458 | 166.071ms | 1811 | 2560 | 98909.1 | 1252.03 | 1.0682 | 1.75666 | 1(Win) | true |
| Glaze | 944.082 | 0.0717565 | 186.319ms | 1811 | 30 | 51.6966 | 1829.4 | 0.0565167 | 2.58649 | 2(Loss) | true |
| simdjson (ondemand) | 435.035 | 0.131171 | 402.792ms | 1811 | 30 | 813.551 | 3970.03 | 0.0587391 | 5.65549 | 3(Loss) | true |
