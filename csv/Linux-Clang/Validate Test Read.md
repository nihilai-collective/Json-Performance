
----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3992.27 | 0.133972 | 7598.77ms | 631514 | 160 | 6.53547e+06 | 150856 | 0.0141463 | 0.620009 | 1(Win) | true |
| Glaze | 2609.41 | 0.275574 | 5873.59ms | 631514 | 40 | 1.61815e+07 | 230802 | 0.129919 | 0.948696 | 2(Loss) | true |
