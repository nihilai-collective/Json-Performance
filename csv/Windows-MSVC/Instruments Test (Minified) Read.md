
----
### Instruments Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 972.66 | 0.565071 | 5496.95ms | 108313 | 80 | 2.88095e+07 | 106199 | 0.973262 | 2.54453 | 1(Win) | true |
| simdjson (ondemand) | 828.508 | 0.504581 | 6642.13ms | 108313 | 80 | 3.16606e+07 | 124676 | 0.362623 | 2.98747 | 2(Loss) | true |
