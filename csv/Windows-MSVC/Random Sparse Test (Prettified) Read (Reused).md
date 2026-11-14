
----
### Random Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2583.99 | 0.115091 | 6993.98ms | 676745 | 80 | 6.61062e+06 | 249766 | 0.0655183 | 1.17608 | 1(Win) | true |
| simdjson (ondemand) | 2198.49 | 0.171522 | 8099.37ms | 676745 | 160 | 4.05658e+07 | 293562 | 0.353813 | 1.38238 | 2(Loss) | true |
