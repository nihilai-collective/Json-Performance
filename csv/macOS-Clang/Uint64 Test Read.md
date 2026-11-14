
----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2189.63 | 0.137891 | 178.23ms | 3873 | 4890 | 26456.7 | 1686.85 | 0.0602793 | 1(Win) | true |
| simdjson (stage-1) | 1254.92 | 0.519322 | 279.109ms | 3873 | 640 | 149527 | 2943.29 | 0.84401 | 2(Loss) | true |
