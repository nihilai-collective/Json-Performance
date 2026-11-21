
----
### Uint64 Test Write Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3100.7 | 0.179312 | 122.368ms | 3873 | 2560 | 11679.9 | 1191.21 | 0.00304959 | 1(Win) | true |
| Glaze | 524.749 | 0.181196 | 755.318ms | 3873 | 1280 | 208208 | 7038.76 | 2.40933 | 2(Loss) | true |
