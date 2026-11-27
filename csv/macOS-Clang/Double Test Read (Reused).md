
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 494.657 | 0.831333 | 370.432ms | 1811 | 320 | 269606 | 3491.52 | 0.883481 | 1(Win) | true |
| simdjson (ondemand) | 261.528 | 0.446621 | 645.531ms | 1811 | 1280 | 1.1135e+06 | 6603.89 | 3.26426 | 2(Loss) | true |
