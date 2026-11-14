
----
### Instruments Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4051.86 | 0.0530653 | 4380.97ms | 183677 | 4890 | 2.57354e+06 | 43231.5 | 0.201473 | 0.749646 | 1(Win) | true |
| simdjson (ondemand) | 3260.42 | 0.0796528 | 5388.52ms | 183677 | 1280 | 2.3441e+06 | 53725.6 | 0.16144 | 0.931757 | 2(Loss) | true |
