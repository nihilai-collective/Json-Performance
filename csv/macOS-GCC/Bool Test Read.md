
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1623.54 | 2.6417 | 57.236ms | 905 | 1280 | 252434 | 531.6 | 0.746826 | 1(Win) | true |
| Glaze | 1338.52 | 2.19577 | 68.3958ms | 905 | 1280 | 256587 | 644.8 | 0.123916 | 2(Loss) | true |
| Jsonifier (two-stage) | 351.072 | 0.873437 | 264.897ms | 905 | 640 | 295086 | 2458.4 | 1.50641 | 3(Loss) | true |
| simdjson (ondemand) | 164.726 | 2.60586 | 533.283ms | 905 | 30 | 559241 | 5239.47 | 0 | 4(Loss) | true |
