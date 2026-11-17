
----
### Bool Test Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 645.193 | 0.741502 | 159.08ms | 905 | 2560 | 251873 | 1337.7 | 1.37163 | 1(Win) | true |
| simdjson (stage-1) | 302.591 | 0.374119 | 326.895ms | 905 | 4890 | 556819 | 2852.28 | 1.20568 | 2(Loss) | true |
