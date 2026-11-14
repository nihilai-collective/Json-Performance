
----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| simdjson (ondemand) STATISTICAL TIE | 1105.24 | 0.450062 | 5534.75ms | 4197496 | 30 | 7.97141e+09 | 3.62188e+06 | 0.696564 | 1(Tie) | true |
| Jsonifier (generic) STATISTICAL TIE | 1100.35 | 0.843225 | 5188.91ms | 4197496 | 40 | 3.76414e+10 | 3.63797e+06 | 0.775508 | 1(Tie) | true |
