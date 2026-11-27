
----
### Apache Builds Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2315.99 | 0.0979736 | 113.248ms | 2632 | 160 | 180.4 | 1083.8 | 0 | 1.04251 | 1(Win) | true |
| Jsonifier (two-stage) | 2002.25 | 0.240035 | 132.029ms | 2632 | 160 | 1448.79 | 1253.62 | 0.359655 | 1.21043 | 2(Loss) | true |
| simdjson (reflection) | 1838.21 | 0.327237 | 141.964ms | 2632 | 2560 | 51115.1 | 1365.5 | 0.114501 | 1.31794 | 3(Loss) | true |
| Glaze | 1748.05 | 0.17966 | 145.909ms | 2632 | 80 | 532.425 | 1435.92 | 0.431647 | 1.38913 | 4(Loss) | true |
| simdjson (ondemand) | 1724.09 | 0.253509 | 148.467ms | 2632 | 2560 | 34872.1 | 1455.88 | 0.500689 | 1.40883 | 5(Loss) | true |
