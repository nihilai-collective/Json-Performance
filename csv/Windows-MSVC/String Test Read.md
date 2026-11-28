
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 622.484 | 0.329823 | 663.37ms | 4215 | 1280 | 580646 | 6457.58 | 0.0616627 | 3.95289 | 1(Win) | true |
| Glaze | 485.085 | 0.150138 | 791.903ms | 4215 | 30 | 4643.68 | 8286.67 | 0.160643 | 5.09183 | 2(Loss) | true |
| simdjson (ondemand) | 388.064 | 0.429488 | 1059.16ms | 4215 | 320 | 633346 | 10358.4 | 0.0994575 | 6.35464 | 3(Loss) | true |
