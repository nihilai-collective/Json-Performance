
----
### Instruments Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5008.92 | 0.0267041 | 2797.92ms | 108313 | 4890 | 148299 | 20622.3 | 0.689722 | 1.02088 | 5.5017 | 0.852382 | 0.000893982 | 3.93467e-06 | 1.35939e-06 | 1(Win) | true |
| simdjson (ondemand) | 4236.31 | 0.0270664 | 3177.07ms | 108313 | 4890 | 212987 | 24383.3 | 0.135911 | 1.2036 | 6.07973 | 0.765467 | 0.00167026 | 6.0927e-06 | 3.45322e-06 | 2(Loss) | true |
