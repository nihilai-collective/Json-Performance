
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 759.129 | 0.808536 | 465.452ms | 4215 | 320 | 586562 | 5295.2 | 0.316265 | 1(Win) | true |
| Glaze | 646.926 | 0.368448 | 658.896ms | 4215 | 640 | 335443 | 6213.6 | 0.374774 | 2(Loss) | true |
| simdjson (reflection) | 573.756 | 0.517965 | 699.723ms | 4215 | 2560 | 3.37117e+06 | 7006 | 1.11224 | 3(Loss) | true |
| simdjson (ondemand) | 486.229 | 0.231021 | 833.118ms | 4215 | 4890 | 1.78373e+06 | 8267.18 | 0.412684 | 4(Loss) | true |
