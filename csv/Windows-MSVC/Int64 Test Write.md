
----
### Int64 Test Write Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 438.113 | 0.207977 | 861.162ms | 3862 | 2560 | 782573 | 8406.72 | 0.0567204 | 5.62864 | 1(Win) | true |
| Glaze | 350.77 | 0.129155 | 1094.37ms | 3862 | 30 | 5517.24 | 10500 | 0.253325 | 7.04122 | 2(Loss) | true |
