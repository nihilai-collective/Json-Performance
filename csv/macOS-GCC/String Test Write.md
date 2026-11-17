
----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1260.59 | 0.246953 | 726.037ms | 9578 | 4890 | 1.56582e+06 | 7246.06 | 0.661387 | 1(Win) | true |
| simdjson (reflection) | 1147.46 | 0.244798 | 791.554ms | 9578 | 4890 | 1.85694e+06 | 7960.45 | 1.46375 | 2(Loss) | true |
| Glaze | 1056.6 | 0.307464 | 880.411ms | 9578 | 1280 | 904336 | 8645 | 0.581903 | 3(Loss) | true |
