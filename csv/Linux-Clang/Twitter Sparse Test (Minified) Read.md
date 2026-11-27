
----
### Twitter Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7080.69 | 0.0667241 | 4310.03ms | 264040 | 160 | 90089.5 | 35562.7 | 0.0955146 | 0.714155 | 3.43058 | 0.483173 | 0.00126018 | 3.00617e-06 | 2.08302e-06 | 1(Win) | true |
| simdjson (ondemand) | 6150.72 | 0.0603019 | 4912.24ms | 264040 | 1280 | 780116 | 40939.6 | 0.0385567 | 0.822487 | 3.88498 | 0.435078 | 0.00103316 | 5.00043e-06 | 2.44695e-06 | 2(Loss) | true |
