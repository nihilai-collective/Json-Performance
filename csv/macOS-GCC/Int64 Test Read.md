
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1171.57 | 1.96431 | 112.203ms | 1313 | 160 | 70523.3 | 1068.8 | 0.595238 | 1(Win) | true |
| Glaze | 806.45 | 0.70099 | 166.204ms | 1313 | 2560 | 303276 | 1552.7 | 0.811294 | 2(Loss) | true |
| simdjson (reflection) | 650.717 | 0.447465 | 196.585ms | 1313 | 2560 | 189803 | 1924.3 | 2.68534 | 3(Loss) | true |
| simdjson (ondemand) | 294.754 | 0.373067 | 431.06ms | 1313 | 1280 | 321509 | 4248.2 | 0.631549 | 4(Loss) | true |
