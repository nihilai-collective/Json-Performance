
----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 934.203 | 0.0548404 | 422.931ms | 3873 | 40 | 188.051 | 3953.72 | 0.267594 | 2.63435 | 1(Win) | true |
| Glaze | 811.769 | 0.117241 | 455.829ms | 3873 | 4890 | 139156 | 4550.04 | 0.399861 | 3.0302 | 2(Loss) | true |
