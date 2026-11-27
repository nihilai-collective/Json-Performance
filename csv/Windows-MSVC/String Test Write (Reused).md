
----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5134.99 | 0.515935 | 92.4595ms | 4215 | 640 | 10439.7 | 782.812 | 0.521669 | 0.576021 | 1(Win) | true |
| Glaze | 1707.57 | 0.313359 | 268.27ms | 4215 | 320 | 17412.9 | 2354.06 | 0.76244 | 1.75978 | 2(Loss) | true |
