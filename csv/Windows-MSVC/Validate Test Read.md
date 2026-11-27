
----
### Validate Test Read Results [(Here is the data we used for this test)](./json/Validate%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Validate%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2724.49 | 0.719756 | 5615.3ms | 631514 | 1280 | 3.24023e+09 | 221054 | 0.447944 | 1.11533 | 1(Win) | true |
| Glaze | 2378.75 | 0.5645 | 7075.42ms | 631514 | 30 | 6.12801e+07 | 253183 | 0.318906 | 1.27747 | 2(Loss) | true |
