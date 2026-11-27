
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 424.183 | 0.412992 | 277.879ms | 1313 | 1280 | 190247 | 2951.97 | 1.15348 | 1(Win) | true |
| simdjson (ondemand) | 247.958 | 0.288599 | 494.413ms | 1313 | 4890 | 1.03866e+06 | 5049.95 | 1.23987 | 2(Loss) | true |
