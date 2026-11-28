
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1082.98 | 0.504077 | 177.259ms | 1811 | 40 | 2584.95 | 1594.78 | 2.85635 | 1(Win) | true |
| Glaze | 979.554 | 0.0648832 | 181.159ms | 1811 | 320 | 418.788 | 1763.15 | 0.0377377 | 2(Loss) | true |
| simdjson (ondemand) | 308.471 | 0.387779 | 548.241ms | 1811 | 160 | 75421.8 | 5598.91 | 0.513211 | 3(Loss) | true |
