
----
### Validate Test Read Results [(View the data used in the following test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2932.9 | 0.0885265 | 5240.69ms | 631514 | 1280 | 4.22987e+07 | 205346 | 0.0642242 | 1.03619 | 1(Win) | true |
| Glaze | 2521.62 | 0.0409848 | 6246.3ms | 631514 | 1280 | 1.22648e+07 | 238838 | 0.131112 | 1.20519 | 2(Loss) | true |
