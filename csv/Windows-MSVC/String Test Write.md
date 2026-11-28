
----
### String Test Write Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 482.338 | 0.153721 | 848.2ms | 4215 | 4890 | 802543 | 8333.87 | 0.10678 | 5.11633 | 1(Win) | true |
| Glaze | 392.297 | 0.185602 | 1043.51ms | 4215 | 30 | 10850.6 | 10246.7 | 1.05194 | 6.29447 | 2(Loss) | true |
