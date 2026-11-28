
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1045.08 | 0.1114 | 176.348ms | 1811 | 160 | 542.279 | 1652.6 | 0.25049 | 1(Win) | true |
| Glaze | 904.539 | 0.233277 | 194.228ms | 1811 | 40 | 793.574 | 1909.38 | 0.0920047 | 2(Loss) | true |
| simdjson (ondemand) | 300.293 | 0.0243419 | 607.554ms | 1811 | 30 | 58.8 | 5751.4 | 0.931306 | 3(Loss) | true |
