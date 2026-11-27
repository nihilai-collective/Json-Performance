
----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1748.9 | 0.139837 | 4701.39ms | 83958 | 1280 | 5.2462e+06 | 45782.2 | 0.031026 | 1(Win) | true |
| Jsonifier | 1657.73 | 0.603629 | 4708ms | 83958 | 640 | 5.4402e+07 | 48300 | 0.785499 | 2(Loss) | true |
| Glaze | 1584.17 | 0.337049 | 5069.14ms | 83958 | 1280 | 3.71465e+07 | 50543 | 0.0605059 | 3(Loss) | true |
| simdjson (ondemand) | 1415.76 | 0.10263 | 5990.68ms | 83958 | 1280 | 4.31218e+06 | 56555 | 0.593726 | 4(Loss) | true |
| simdjson (reflection) | 1011.59 | 0.173581 | 8106.67ms | 83958 | 320 | 6.04043e+06 | 79151.2 | 0.0252745 | 5(Loss) | true |
