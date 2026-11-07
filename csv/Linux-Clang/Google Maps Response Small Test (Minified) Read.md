
----
### Google Maps Response Small Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2463.34 | 0.131632 | 170.674ms | 4390 | 40 | 200.199 | 1699.58 | 0.0171582 | 0.98992 | 1(Win) | true |
| Jsonifier (two-stage) | 1925.83 | 0.0981622 | 221.99ms | 4390 | 30 | 136.616 | 2173.93 | 0.259987 | 1.27036 | 2(Loss) | true |
| Glaze | 1669.96 | 0.14559 | 251.802ms | 4390 | 40 | 532.897 | 2507.03 | 0.0441896 | 1.46671 | 3(Loss) | true |
| simdjson (ondemand) | 1025.28 | 0.1745 | 412.13ms | 4390 | 2560 | 129980 | 4083.42 | 0.201629 | 2.39888 | 4(Loss) | true |
