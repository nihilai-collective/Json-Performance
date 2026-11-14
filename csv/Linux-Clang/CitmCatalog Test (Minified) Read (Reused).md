
----
### CitmCatalog Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/CitmCatalog%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2683.07 | 0.196313 | 5585.61ms | 500299 | 640 | 7.79957e+07 | 177827 | 0.00237761 | 1.88133 | 8.80544 | 1.6479 | 0.00900578 | 0.00299199 | 2.0316e-05 | 1(Win) | true |
| Glaze | 2115.65 | 0.083971 | 6886.51ms | 500299 | 1280 | 4.59031e+07 | 225521 | 0.10431 | 2.38093 | 11.3989 | 2.0915 | 0.00968341 | 0.00184302 | 2.1926e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1936.63 | 0.249081 | 7445.6ms | 500299 | 1280 | 4.82012e+08 | 246368 | 0.209064 | 2.60162 | 12.1486 | 2.02831 | 0.0114281 | 0.0249122 | 3.79539e-05 | 3(Loss) | true |
| simdjson (ondemand) | 1291.36 | 0.571186 | 5249.7ms | 500299 | 30 | 1.3361e+08 | 369472 | 0.197163 | 3.9117 | 17.7712 | 2.5822 | 0.00876309 | 0.0211124 | 9.20116e-05 | 4(Loss) | true |
