
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 1763.63 | 0.499381 | 53.1968ms | 905 | 160 | 955.582 | 489.375 | 0.381679 | 1.6621 | 1(Win) | true |
| simdjson (stage-1) | 739.251 | 0.75774 | 119.984ms | 905 | 160 | 12522 | 1167.5 | 0.106952 | 4.03537 | 2(Loss) | true |
