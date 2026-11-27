
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 669.29 | 0.426274 | 189.794ms | 1313 | 2560 | 162824 | 1870.9 | 0.250586 | 1(Win) | true |
| simdjson (ondemand) | 310.128 | 0.341623 | 410.654ms | 1313 | 320 | 60882.1 | 4037.6 | 0.0198098 | 2(Loss) | true |
