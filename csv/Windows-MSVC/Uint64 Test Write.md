
----
### Uint64 Test Write Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Uint64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 617.375 | 0.264192 | 188.765ms | 1213 | 80 | 1960.44 | 1873.75 | 0.469169 | 3.94191 | 1(Win) | true |
| Glaze | 120.689 | 0.137509 | 961.963ms | 1213 | 40 | 6948.72 | 9585 | 0.0521376 | 20.4404 | 2(Loss) | true |
