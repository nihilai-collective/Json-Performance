
----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2083.99 | 0.174979 | 179.489ms | 3873 | 4890 | 47031.1 | 1772.36 | 1.00895 | 1(Win) | true |
| simdjson (stage-1) | 1436.7 | 0.446249 | 288.713ms | 3873 | 40 | 5264.73 | 2570.88 | 0.161359 | 2(Loss) | true |
