
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 512.558 | 0.281026 | 766.301ms | 4215 | 40 | 19429.5 | 7842.5 | 0.159642 | 4.8232 | 1(Win) | true |
| Glaze | 415.405 | 0.146007 | 1005.39ms | 4215 | 30 | 5988.51 | 9676.67 | 0.171939 | 5.94182 | 2(Loss) | true |
