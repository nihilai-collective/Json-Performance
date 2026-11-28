
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1440.03 | 0.0925798 | 90.9884ms | 1313 | 80 | 51.8456 | 869.55 | 0.409931 | 1.66431 | 1(Win) | true |
| Glaze | 859.117 | 0.0407857 | 149.088ms | 1313 | 160 | 56.5407 | 1457.51 | 0.0728451 | 2.82741 | 2(Loss) | true |
| simdjson (ondemand) | 335.037 | 0.0693889 | 363.843ms | 1313 | 40 | 269.02 | 3737.43 | 0.0568897 | 7.33701 | 3(Loss) | true |
