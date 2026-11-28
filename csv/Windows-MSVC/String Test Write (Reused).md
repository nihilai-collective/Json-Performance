
----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3527.05 | 0.240353 | 129.506ms | 4215 | 320 | 2401.16 | 1139.69 | 0.463974 | 0.68491 | 1(Win) | true |
| Glaze | 1813.42 | 0.379809 | 267.481ms | 4215 | 30 | 2126.44 | 2216.67 | 0.15015 | 1.34389 | 2(Loss) | true |
