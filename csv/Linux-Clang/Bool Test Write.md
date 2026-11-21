
----
### Bool Test Write Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2170.71 | 0.186045 | 42.5378ms | 905 | 40 | 21.8872 | 397.6 | 0.409117 | 1.07 | 1(Win) | true |
| Glaze | 193.598 | 0.11673 | 443.977ms | 905 | 4890 | 132425 | 4458.09 | 1.84275 | 12.7125 | 2(Loss) | true |
