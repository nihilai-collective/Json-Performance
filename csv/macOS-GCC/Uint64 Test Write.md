
----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) STATISTICAL TIE | 750.057 | 0.589988 | 502.018ms | 3873 | 640 | 540223 | 4924.4 | 0.629393 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 743.894 | 0.214324 | 500.863ms | 3873 | 4890 | 553764 | 4965.2 | 0.826397 | 1(Tie) | true |
| Glaze | 514.049 | 0.188986 | 719.535ms | 3873 | 4890 | 901683 | 7185.28 | 0.707855 | 3(Loss) | true |
