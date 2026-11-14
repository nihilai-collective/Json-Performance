
----
### Int64 Test Read Results [(View the data used in the following test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2361.78 | 0.632038 | 171.763ms | 3862 | 4890 | 475052 | 1559.45 | 2.08128 | 1(Win) | true |
| Glaze | 1315.62 | 0.423766 | 302.158ms | 3862 | 2560 | 360291 | 2799.5 | 0.628283 | 2(Loss) | true |
| Jsonifier (two-stage) | 861.844 | 0.339264 | 451.166ms | 3862 | 2560 | 538125 | 4273.5 | 2.0318 | 3(Loss) | true |
| simdjson (ondemand) | 386.626 | 0.272086 | 952.883ms | 3862 | 4890 | 3.28523e+06 | 9526.24 | 1.10523 | 4(Loss) | true |
