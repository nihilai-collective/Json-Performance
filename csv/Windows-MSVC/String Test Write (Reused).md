
----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7592.12 | 0.374589 | 130.864ms | 9578 | 4890 | 99321.4 | 1203.13 | 0.326053 | 0.317227 | 1(Win) | true |
| Glaze | 2482.99 | 0.0881873 | 388.513ms | 9578 | 160 | 1683.96 | 3678.75 | 0.271095 | 0.987908 | 2(Loss) | true |
