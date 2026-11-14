
----
### Instruments Test (Prettified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 22631.5 | 0.11141 | 803.431ms | 183677 | 40 | 2974.36 | 7740 | 0.0862069 | 0.109161 | 1(Win) | true |
| simdjson (stage-1) | 21087.6 | 0.0988574 | 849.571ms | 183677 | 30 | 2022.99 | 8306.67 | 0.12053 | 0.116766 | 2(Loss) | true |
