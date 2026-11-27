
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (stage-1) | 1497.36 | 0.0948465 | 61.3405ms | 905 | 1280 | 382.559 | 576.398 | 0.0149116 | 1(Win) | true |
| simdjson (stage-1) | 553.284 | 0.156231 | 170.646ms | 905 | 80 | 475.144 | 1559.91 | 0.0984662 | 2(Loss) | true |
