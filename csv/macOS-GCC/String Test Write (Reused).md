
----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 4999.67 | 1.98496 | 88.1569ms | 4215 | 640 | 163003 | 804 | 4.82955 | 1(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 4975.54 | 0.999413 | 89.451ms | 4215 | 2560 | 166896 | 807.9 | 2.91997 | 1(Tie) | true |
| Glaze | 2632.79 | 1.30732 | 180.543ms | 4215 | 640 | 254983 | 1526.8 | 1.89536 | 3(Loss) | true |
