
----
### Package.json Corpus 1024-2048 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%201024-2048%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Package.json%20Corpus%201024-2048%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3441.87 | 0.783108 | 4392.74ms | 152326 | 320 | 3.49584e+07 | 42206.5 | 0.506525 | 1(Win) | true |
| simdjson (ondemand) | 3154.82 | 0.287512 | 4520.77ms | 152326 | 4890 | 8.5708e+07 | 46046.9 | 1.98375 | 2(Loss) | true |
