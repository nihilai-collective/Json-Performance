
----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 923.366 | 0.04926 | 397.325ms | 3873 | 80 | 310.617 | 4000.12 | 0.197257 | 2.66333 | 1(Win) | true |
| simdjson (reflection) | 882.443 | 0.0253579 | 425.428ms | 3873 | 160 | 180.247 | 4185.63 | 0.452327 | 2.78802 | 2(Loss) | true |
| Glaze | 785.576 | 0.0395617 | 485.332ms | 3873 | 40 | 138.397 | 4701.75 | 0.0869226 | 3.13349 | 3(Loss) | true |
