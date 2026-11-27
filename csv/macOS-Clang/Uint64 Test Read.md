
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1072.96 | 0.135981 | 111.26ms | 1213 | 160 | 343.902 | 1078.15 | 0.0440375 | 1(Win) | true |
| Glaze | 632.38 | 0.08731 | 178.166ms | 1213 | 320 | 816.288 | 1829.29 | 0.0916523 | 2(Loss) | true |
| simdjson (ondemand) | 274.49 | 0.0825265 | 425.299ms | 1213 | 4890 | 59151.4 | 4214.39 | 0.00754595 | 3(Loss) | true |
