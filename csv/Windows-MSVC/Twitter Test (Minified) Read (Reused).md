
----
### Twitter Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1761.7 | 0.978273 | 7450.24ms | 466906 | 30 | 1.83415e+08 | 252753 | 0.966486 | 1.4052 | 1(Win) | true |
| Jsonifier (two-stage) | 1471.34 | 0.149713 | 8672.18ms | 466906 | 640 | 1.31382e+08 | 302634 | 1.57806 | 1.68226 | 2(Loss) | true |
| Glaze | 1426.62 | 0.371962 | 9036.34ms | 466906 | 40 | 5.39139e+07 | 312120 | 0.0662577 | 1.73527 | 3(Loss) | true |
| simdjson (ondemand) | 1368.81 | 0.298562 | 9424.34ms | 466906 | 40 | 3.77315e+07 | 325302 | 0.100574 | 1.80848 | 4(Loss) | true |
