
----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3079.08 | 0.462751 | 5576.76ms | 631514 | 30 | 2.45776e+07 | 195597 | 0.806343 | 0.803948 | 1(Win) | true |
| Glaze | 2503.64 | 0.145972 | 6528.92ms | 631514 | 320 | 3.94556e+07 | 240553 | 0.000519633 | 0.988767 | 2(Loss) | true |
