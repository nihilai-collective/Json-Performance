
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1262.14 | 0.477257 | 71.9163ms | 905 | 1280 | 13633.2 | 683.821 | 0.00422699 | 1(Win) | true |
| Glaze | 1168.41 | 0.155147 | 74.7297ms | 905 | 320 | 420.288 | 738.678 | 0.507193 | 2(Loss) | true |
| simdjson (ondemand) | 311.065 | 0.0306483 | 284.451ms | 905 | 1280 | 925.586 | 2774.58 | 0.151152 | 3(Loss) | true |
