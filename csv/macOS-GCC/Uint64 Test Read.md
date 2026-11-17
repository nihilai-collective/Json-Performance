
----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2645.21 | 0.525381 | 137.47ms | 3873 | 4890 | 263167 | 1396.33 | 3.31673 | 1(Win) | true |
| simdjson (stage-1) | 1308.76 | 0.485758 | 284.131ms | 3873 | 2560 | 481122 | 2822.2 | 3.68112 | 2(Loss) | true |
