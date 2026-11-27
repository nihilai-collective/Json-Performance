
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1653.4 | 3.80827 | 59.6562ms | 905 | 640 | 252916 | 522 | 1.31988 | 1(Win) | true |
| Glaze | 1279.39 | 1.96256 | 81.887ms | 905 | 1280 | 224361 | 674.6 | 0.207962 | 2(Loss) | true |
| simdjson (reflection) | 864.458 | 2.72155 | 111.915ms | 905 | 80 | 59065.4 | 998.4 | 0.636943 | 3(Loss) | true |
| simdjson (ondemand) | 381.093 | 0.343345 | 235.514ms | 905 | 4890 | 295669 | 2264.74 | 0.542963 | 4(Loss) | true |
