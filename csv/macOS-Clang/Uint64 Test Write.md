
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1053.32 | 0.139066 | 116.431ms | 1213 | 4890 | 11406.5 | 1098.25 | 0.858425 | 1(Win) | true |
| Glaze | 162.358 | 0.092931 | 742.44ms | 1213 | 30 | 1315.27 | 7125.03 | 0.214276 | 2(Loss) | true |
