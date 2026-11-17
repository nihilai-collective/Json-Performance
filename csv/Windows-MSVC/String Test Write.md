
----
### String Test Write Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Write_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1164.16 | 0.315742 | 802.394ms | 9578 | 80 | 49099.7 | 7846.25 | 0.0159337 | 2.6032 | 1(Win) | true |
| Glaze | 887.356 | 0.227718 | 1046.11ms | 9578 | 1280 | 703332 | 10293.8 | 0.0462745 | 3.41755 | 2(Loss) | true |
