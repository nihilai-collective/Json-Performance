
----
### Double Test Write (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 729.313 | 0.156054 | 248.421ms | 1811 | 160 | 2185.14 | 2368.12 | 0.0263852 | 3.35803 | 1(Win) | true |
| Glaze | 386.958 | 0.117685 | 466.105ms | 1798 | 80 | 2175.63 | 4431.25 | 0.0282167 | 6.35861 | 2(Loss) | true |
