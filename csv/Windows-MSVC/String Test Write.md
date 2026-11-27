
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 581.517 | 0.344324 | 714.407ms | 4215 | 40 | 22660.3 | 6912.5 | 0.521086 | 5.20888 | 1(Win) | true |
| Glaze | 458.253 | 0.986559 | 936.49ms | 4215 | 160 | 1.19826e+06 | 8771.88 | 0.826738 | 6.61466 | 2(Loss) | true |
