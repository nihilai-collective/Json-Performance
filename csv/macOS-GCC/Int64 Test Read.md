
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1170.15 | 0.568232 | 110.894ms | 1313 | 2560 | 94654.2 | 1070.1 | 0.667921 | 1(Win) | true |
| Glaze | 738.049 | 0.83432 | 198.263ms | 1313 | 1280 | 256469 | 1696.6 | 2.4494 | 2(Loss) | true |
| simdjson (reflection) | 663.628 | 0.336482 | 197.644ms | 1313 | 4890 | 197111 | 1886.86 | 0.738527 | 3(Loss) | true |
| simdjson (ondemand) | 268.943 | 0.264769 | 444.365ms | 1313 | 4890 | 743105 | 4655.9 | 2.75434 | 4(Loss) | true |
