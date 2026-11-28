
----
### Bool Test Write Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 858.248 | 0.201963 | 105.013ms | 905 | 160 | 659.984 | 1005.62 | 0.0621118 | 2.80349 | 1(Win) | true |
| Glaze | 84.955 | 0.302251 | 1139.51ms | 905 | 4890 | 4.61068e+06 | 10159.2 | 0.185514 | 29.0419 | 2(Loss) | true |
