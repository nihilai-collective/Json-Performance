
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2813.73 | 0.723208 | 133.543ms | 3873 | 2560 | 230726 | 1312.7 | 2.45863 | 1(Win) | true |
| Glaze | 1519.49 | 0.3712 | 240.677ms | 3873 | 4890 | 398127 | 2430.8 | 0.787624 | 2(Loss) | true |
| Jsonifier (two-stage) | 829.235 | 0.309147 | 455.497ms | 3873 | 2560 | 485412 | 4454.2 | 0.355984 | 3(Loss) | true |
| simdjson (ondemand) | 422.645 | 0.224232 | 887.808ms | 3873 | 2560 | 983055 | 8739.2 | 0.231678 | 4(Loss) | true |
