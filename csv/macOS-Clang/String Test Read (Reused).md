
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1634.42 | 0.128404 | 310.354ms | 4215 | 40 | 398.917 | 2459.43 | 0.0125352 | 1(Win) | true |
| Glaze | 994.043 | 0.30847 | 468.553ms | 4215 | 40 | 6223.99 | 4043.82 | 0.358313 | 2(Loss) | true |
| simdjson (ondemand) | 820.69 | 0.109905 | 601.415ms | 4215 | 40 | 1159.13 | 4898 | 0.094507 | 3(Loss) | true |
