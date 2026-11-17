
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2601.7 | 0.0847463 | 744.056ms | 905 | 1280 | 101.166 | 331.735 | 0.12096 | 2.22573 | 11.0365 | 1.73039 | 0.00111533 | 9.75483e-05 | 8.6326e-07 | 1(Win) | true |
| Glaze | 1888.64 | 0.152964 | 754.623ms | 905 | 4890 | 2389.38 | 456.983 | 0.117053 | 2.9655 | 13.6652 | 2.06519 | 0.00114226 | 3.00534e-05 | 2.71159e-06 | 2(Loss) | true |
| Jsonifier (two-stage) | 620.081 | 0.0805868 | 852.295ms | 905 | 4890 | 6152.3 | 1391.88 | 0.123236 | 8.49274 | 42.2144 | 4.29172 | 0.00546475 | 0.000131512 | 2.25966e-05 | 3(Loss) | true |
| simdjson (ondemand) | 223.725 | 0.0873751 | 1103.01ms | 905 | 160 | 1817.87 | 3857.75 | 0.0961423 | 23.0737 | 104.842 | 9.68508 | 0.0916506 | 7.59669e-05 | 0 | 4(Loss) | true |
