
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 846.801 | 0.157482 | 106.804ms | 905 | 640 | 1648.84 | 1019.22 | 0.138164 | 2.84974 | 1(Win) | true |
| Glaze | 84.6152 | 0.462214 | 1106.1ms | 905 | 2560 | 5.69018e+06 | 10200 | 0.156495 | 29.1645 | 2(Loss) | true |
