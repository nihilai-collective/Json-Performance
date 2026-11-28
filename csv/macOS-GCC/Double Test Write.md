
----
### Double Test Write Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (reflection) | 311.541 | 0.240939 | 619.078ms | 1997 | 4890 | 1.06084e+06 | 6113.11 | 0.338325 | 1(Win) | true |
| Jsonifier | 308.045 | 0.194182 | 630.28ms | 1997 | 2560 | 368966 | 6182.5 | 0.250081 | 2(Loss) | true |
| Glaze | 204.408 | 0.171986 | 845.817ms | 1798 | 4890 | 1.01784e+06 | 8388.63 | 0.197479 | 3(Loss) | true |
