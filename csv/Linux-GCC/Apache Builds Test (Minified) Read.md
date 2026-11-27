
----
### Apache Builds Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1574.42 | 0.193855 | 5787.66ms | 94653 | 160 | 1.97651e+06 | 57334.1 | 0.0570449 | 1.57176 | 1(Win) | true |
| simdjson (reflection) STATISTICAL TIE | 1389.16 | 0.109416 | 6532.18ms | 94653 | 2560 | 1.29408e+07 | 64980.2 | 0.212416 | 1.78148 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1388.73 | 0.281372 | 6627.75ms | 94653 | 80 | 2.67598e+06 | 65000.4 | 0.164288 | 1.78206 | 2(Tie) | true |
| Glaze | 1345.64 | 0.374125 | 6737.43ms | 94653 | 80 | 5.03887e+06 | 67081.8 | 0.197205 | 1.8391 | 4(Loss) | true |
| simdjson (ondemand) | 1283.15 | 0.12078 | 6975.38ms | 94653 | 1280 | 9.24103e+06 | 70349.1 | 0.39295 | 1.92873 | 5(Loss) | true |
