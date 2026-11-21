
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze STATISTICAL TIE | 1434.63 | 0.0779249 | 62.0821ms | 905 | 30 | 6.5931 | 601.6 | 0.00554109 | 1.64707 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 1433.12 | 0.220731 | 61.9886ms | 905 | 30 | 53.0126 | 602.233 | 0.160772 | 1.65179 | 1(Tie) | true |
| Jsonifier (two-stage) | 1380.89 | 0.031607 | 65.0804ms | 905 | 640 | 24.9763 | 625.016 | 0.0624594 | 1.71725 | 3(Loss) | true |
| simdjson (ondemand) | 381.487 | 0.0536388 | 225.149ms | 905 | 30 | 44.1793 | 2262.4 | 0.309916 | 6.41134 | 4(Loss) | true |
