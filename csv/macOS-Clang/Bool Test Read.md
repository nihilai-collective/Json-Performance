
----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 484.499 | 0.593327 | 187.832ms | 905 | 320 | 35747.9 | 1781.38 | 2.55893 | 1(Win) | true |
| simdjson (stage-1) | 375.122 | 0.0764362 | 268.654ms | 905 | 160 | 494.848 | 2300.79 | 0.0347828 | 2(Loss) | true |
