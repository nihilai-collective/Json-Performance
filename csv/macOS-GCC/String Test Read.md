
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 604.654 | 0.444098 | 673.589ms | 4215 | 320 | 278926 | 6648 | 0.144613 | 1(Win) | true |
| simdjson (ondemand) | 486.981 | 0.536937 | 873.672ms | 4215 | 640 | 1.25718e+06 | 8254.4 | 0.398949 | 2(Loss) | true |
