
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 722.008 | 0.0916966 | 590.757ms | 3862 | 320 | 7001.61 | 5101.18 | 0.0998159 | 1(Win) | true |
| simdjson (ondemand) | 415.435 | 0.544825 | 996.309ms | 3862 | 320 | 746589 | 8865.62 | 0.821085 | 2(Loss) | true |
