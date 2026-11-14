
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1266.99 | 0.0686838 | 71.8255ms | 905 | 2560 | 560.399 | 681.2 | 0.202757 | 1(Win) | true |
| Glaze | 1200.01 | 0.287275 | 75.1683ms | 905 | 80 | 341.518 | 719.225 | 0.0868236 | 2(Loss) | true |
| Jsonifier (two-stage) | 346.308 | 0.105029 | 250.75ms | 905 | 160 | 1096.26 | 2492.22 | 2.36548 | 3(Loss) | true |
| simdjson (ondemand) | 184.657 | 0.138692 | 476.78ms | 905 | 40 | 1680.84 | 4673.93 | 0.00766723 | 4(Loss) | true |
