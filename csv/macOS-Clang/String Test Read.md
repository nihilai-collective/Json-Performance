
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) | 629.6 | 0.306912 | 667.551ms | 4215 | 1280 | 491477 | 6384.59 | 1.40128 | 1(Win) | true |
| Jsonifier (generic) | 528.548 | 1.56211 | 719.214ms | 4215 | 80 | 1.12912e+06 | 7605.25 | 3.91496 | 2(Loss) | true |
