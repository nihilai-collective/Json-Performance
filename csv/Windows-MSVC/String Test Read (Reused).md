
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1188.83 | 0.273851 | 465.519ms | 4215 | 80 | 6859.18 | 3381.25 | 0.697504 | 2.53992 | 1(Win) | true |
| Glaze | 849.24 | 0.25492 | 601.844ms | 4215 | 30 | 4367.82 | 4733.33 | 0.141044 | 3.56233 | 2(Loss) | true |
| simdjson (ondemand) | 688.606 | 0.170066 | 721.076ms | 4215 | 40 | 3942.31 | 5837.5 | 0.0714286 | 4.4026 | 3(Loss) | true |
