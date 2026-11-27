
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 916.242 | 1.29395 | 438.658ms | 4215 | 160 | 515622 | 4387.2 | 0.808824 | 1(Win) | true |
| simdjson (reflection) | 682.723 | 0.230551 | 593.895ms | 4215 | 1280 | 235858 | 5887.8 | 0.0101895 | 2(Loss) | true |
| Glaze | 649.451 | 0.144579 | 628.631ms | 4215 | 4890 | 391580 | 6189.44 | 0.605333 | 3(Loss) | true |
| simdjson (ondemand) | 474.216 | 0.288032 | 847.158ms | 4215 | 1280 | 763017 | 8476.6 | 0.345638 | 4(Loss) | true |
