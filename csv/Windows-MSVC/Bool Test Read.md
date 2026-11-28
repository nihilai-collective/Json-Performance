
----
### Bool Test Read Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 497.696 | 0.327171 | 178.179ms | 905 | 2560 | 82405.7 | 1734.14 | 0.00901104 | 4.89528 | 1(Win) | true |
| Glaze | 453.653 | 0.131406 | 205.538ms | 905 | 40 | 250 | 1902.5 | 0.307557 | 5.36514 | 2(Loss) | true |
| simdjson (ondemand) | 151.85 | 0.085392 | 587.161ms | 905 | 80 | 1884.49 | 5683.75 | 0.0219974 | 16.2098 | 3(Loss) | true |
