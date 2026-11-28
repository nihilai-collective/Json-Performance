
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 836.469 | 1.3078 | 475.372ms | 4215 | 320 | 1.26395e+06 | 4805.6 | 0.720993 | 1(Win) | true |
| simdjson (reflection) | 554.616 | 0.293305 | 713.769ms | 4215 | 4890 | 2.20982e+06 | 7247.78 | 0.146245 | 2(Loss) | true |
| Glaze | 543.142 | 0.473953 | 711.006ms | 4215 | 2560 | 3.14978e+06 | 7400.9 | 0.239733 | 3(Loss) | true |
| simdjson (ondemand) | 437.556 | 0.470446 | 906.671ms | 4215 | 2560 | 4.78176e+06 | 9186.8 | 1.45555 | 4(Loss) | true |
