
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1718.52 | 1.13509 | 775.328ms | 9578 | 160 | 582395 | 5315.2 | 0.835821 | 1(Win) | true |
| Glaze | 1650.93 | 1.03296 | 895.15ms | 9578 | 80 | 261304 | 5532.8 | 1.46714 | 2(Loss) | true |
| simdjson (ondemand) | 913.101 | 0.57595 | 1306.32ms | 9578 | 1280 | 4.24905e+06 | 10003.6 | 2.04841 | 3(Loss) | true |
| Jsonifier (two-stage) | 841.931 | 0.308415 | 1405.05ms | 9578 | 4890 | 5.47491e+06 | 10849.2 | 4.93067 | 4(Loss) | true |
