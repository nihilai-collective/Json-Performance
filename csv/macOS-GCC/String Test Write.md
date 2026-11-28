
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 880.492 | 2.08401 | 499.451ms | 4215 | 30 | 271560 | 4565.33 | 0 | 1(Win) | true |
| simdjson (reflection) | 657.56 | 0.287367 | 586.081ms | 4215 | 4890 | 1.50907e+06 | 6113.11 | 0.272236 | 2(Loss) | true |
| Glaze | 514.085 | 0.639199 | 807.222ms | 4215 | 160 | 399685 | 7819.2 | 3.79921 | 3(Loss) | true |
