
----
### Int64 Test Read Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Int64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1094.91 | 0.101508 | 118.225ms | 1313 | 320 | 431.242 | 1143.63 | 0.0582365 | 1(Win) | true |
| Glaze | 676.029 | 0.0877072 | 182.639ms | 1313 | 320 | 844.539 | 1852.25 | 0.0820622 | 2(Loss) | true |
| simdjson (ondemand) | 306.028 | 0.0746143 | 416.702ms | 1313 | 40 | 372.831 | 4091.7 | 0.103569 | 3(Loss) | true |
