
----
### String Test Read (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1504.39 | 2.22771 | 376.223ms | 4215 | 80 | 283454 | 2672 | 0.119904 | 1(Win) | true |
| simdjson (reflection) | 804.291 | 0.255693 | 600.447ms | 4215 | 4890 | 798576 | 4997.86 | 0.324455 | 2(Loss) | true |
| Glaze | 797.21 | 0.338708 | 607.566ms | 4215 | 4890 | 1.4263e+06 | 5042.26 | 0.128235 | 3(Loss) | true |
| simdjson (ondemand) | 640.698 | 0.405921 | 750.267ms | 4215 | 2560 | 1.66039e+06 | 6274 | 0.496556 | 4(Loss) | true |
