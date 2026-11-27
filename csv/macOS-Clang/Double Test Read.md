
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (stage-1) | 1860.87 | 0.428961 | 104.337ms | 1811 | 160 | 2536.08 | 928.119 | 1.65455 | 1(Win) | true |
| simdjson (stage-1) | 1079.52 | 0.205341 | 171.435ms | 1811 | 40 | 431.702 | 1599.88 | 0.0973087 | 2(Loss) | true |
