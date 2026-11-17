
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 678.767 | 0.267721 | 8123.68ms | 1834197 | 40 | 1.90404e+09 | 2.57706e+06 | 0.910337 | 3.64745 | 1(Win) | true |
| Jsonifier (two-stage) | 597.388 | 0.280599 | 9193.99ms | 1834197 | 80 | 5.4006e+09 | 2.92813e+06 | 0.354163 | 4.14435 | 2(Loss) | true |
| simdjson (ondemand) | 219.857 | 0.413005 | 5608.91ms | 1834197 | 40 | 4.319e+10 | 7.9562e+06 | 0.349663 | 11.261 | 3(Loss) | true |
| Glaze | 194.336 | 0.924404 | 6296.36ms | 1834197 | 40 | 2.7693e+11 | 9.00106e+06 | 0.668597 | 12.7398 | 4(Loss) | true |
