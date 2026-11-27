
----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4832.42 | 0.0768102 | 876.857ms | 7932 | 80 | 115.655 | 1565.38 | 0.0686265 | 1.09506 | 4.9884 | 0.823122 | 0.000882501 | 1.10313e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 3976.91 | 0.073898 | 907.616ms | 7932 | 1280 | 2529.01 | 1902.12 | 0.00628372 | 1.32362 | 6.23765 | 0.917045 | 0.00175821 | 3.28968e-05 | 1.48725e-05 | 2(Loss) | true |
