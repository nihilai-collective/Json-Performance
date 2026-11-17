
----
### Uint64 Test Read Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2804.27 | 0.0505239 | 135.047ms | 3873 | 80 | 35.4272 | 1317.12 | 0.0664767 | 0.864633 | 1(Win) | true |
| Glaze | 1837.87 | 0.0272131 | 207.869ms | 3873 | 160 | 47.8566 | 2009.71 | 0.294262 | 1.32972 | 2(Loss) | true |
| Jsonifier (two-stage) | 794.945 | 0.0431364 | 468.726ms | 3873 | 80 | 321.366 | 4646.34 | 0.00349726 | 3.09634 | 3(Loss) | true |
| simdjson (ondemand) | 415.057 | 0.0279467 | 918.421ms | 3873 | 30 | 185.551 | 8898.97 | 0.0561547 | 5.94758 | 4(Loss) | true |
