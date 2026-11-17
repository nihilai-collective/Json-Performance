
----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1225.92 | 0.156683 | 770.377ms | 9578 | 4890 | 666464 | 7450.96 | 0.166786 | 2.01151 | 1(Win) | true |
| Glaze | 803.132 | 0.102687 | 1227.02ms | 9578 | 30 | 4091.95 | 11373.3 | 0.292227 | 3.0783 | 2(Loss) | true |
