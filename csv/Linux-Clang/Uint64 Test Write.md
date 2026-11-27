
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 323.431 | 0.12868 | 360.654ms | 1213 | 40 | 847.302 | 3576.68 | 0.13742 | 7.59893 | 1(Win) | true |
| Glaze | 260.322 | 0.180304 | 445.765ms | 1213 | 4890 | 313920 | 4443.76 | 0.1604 | 9.45349 | 2(Loss) | true |
