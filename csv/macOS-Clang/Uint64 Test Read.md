
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1023.75 | 0.153003 | 118.889ms | 1213 | 320 | 956.494 | 1129.97 | 0.185082 | 1(Win) | true |
| Glaze | 612.055 | 0.208274 | 194.526ms | 1213 | 80 | 1239.66 | 1890.04 | 0.0323963 | 2(Loss) | true |
| simdjson (ondemand) | 247.361 | 0.184516 | 483.39ms | 1213 | 30 | 2233.83 | 4676.6 | 0.319012 | 3(Loss) | true |
