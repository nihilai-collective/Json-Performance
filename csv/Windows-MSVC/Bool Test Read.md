
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 520.971 | 0.555445 | 168.106ms | 905 | 30 | 2540.23 | 1656.67 | 1.222 | 4.654 | 1(Win) | true |
| Glaze | 504.873 | 0.268608 | 175.457ms | 905 | 4890 | 103105 | 1709.49 | 0.247193 | 4.83077 | 2(Loss) | true |
| simdjson (ondemand) | 155.182 | 0.145968 | 557.531ms | 905 | 4890 | 322286 | 5561.7 | 0.027014 | 15.8538 | 3(Loss) | true |
