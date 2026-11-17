
----
### Discord Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) STATISTICAL TIE | 2976.84 | 0.357755 | 2665.96ms | 83958 | 80 | 740753 | 26897.2 | 0.00706345 | 0.830829 | 1(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 2966.21 | 0.105486 | 2710.71ms | 83958 | 2560 | 2.07563e+06 | 26993.6 | 0.545849 | 0.833771 | 1(Tie) | true |
