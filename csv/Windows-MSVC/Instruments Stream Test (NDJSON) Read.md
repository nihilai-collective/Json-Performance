
----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1135.24 | 0.188985 | 5512.22ms | 4197496 | 80 | 3.55264e+09 | 3.52618e+06 | 0.915845 | 2.67679 | 1(Win) | true |
| simdjson (ondemand) | 966.547 | 0.159234 | 6474.67ms | 4197496 | 80 | 3.47933e+09 | 4.14159e+06 | 0.109165 | 3.14416 | 2(Loss) | true |
