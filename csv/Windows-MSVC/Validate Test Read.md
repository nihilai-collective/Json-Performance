
----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3570.23 | 0.207143 | 8829.43ms | 631514 | 320 | 3.90719e+07 | 168689 | 0.324432 | 0.693313 | 1(Win) | true |
| Glaze | 2470.25 | 0.352304 | 6113.57ms | 631514 | 40 | 2.95107e+07 | 243805 | 0.0951117 | 1.00217 | 2(Loss) | true |
