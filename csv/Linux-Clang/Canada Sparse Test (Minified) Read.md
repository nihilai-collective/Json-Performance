
----
### Canada Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6952.39 | 0.260428 | 7483.91ms | 2090234 | 30 | 1.6727e+07 | 286722 | 0.465028 | 0.74043 | 3.65785 | 0.418406 | 0.0030957 | 0.0498074 | 0.000123001 | 1(Win) | true |
| Jsonifier (generic) | 6875.02 | 0.141241 | 7587.63ms | 2090234 | 320 | 5.36677e+07 | 289948 | 0.0556093 | 0.742692 | 3.27973 | 0.436447 | 0.0058896 | 0.0508466 | 7.63147e-05 | 2(Loss) | true |
