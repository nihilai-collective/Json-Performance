
----
### Google Maps Response Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2180.42 | 0.149172 | 936.71ms | 4390 | 1280 | 10501.2 | 1920.11 | 0.0594909 | 2.4094 | 10.6089 | 1.90205 | 0.00282727 | 8.09724e-05 | 4.96512e-05 | 1(Win) | true |
| simdjson (ondemand) | 1958.76 | 0.0766481 | 933.094ms | 4390 | 2560 | 6870.84 | 2137.39 | 0.0537414 | 2.676 | 11.6948 | 1.87335 | 0.0016788 | 4.71597e-05 | 2.42917e-05 | 2(Loss) | true |
