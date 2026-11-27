
----
### Canada Sparse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 7001.69 | 0.121806 | 7458.26ms | 2090234 | 640 | 7.6966e+07 | 284703 | 0.233403 | 0.729564 | 3.65776 | 0.418389 | 0.00269107 | 0.0497563 | 0.000193209 | 1(Win) | true |
| Jsonifier (generic) | 6843.2 | 0.126291 | 7652.93ms | 2090234 | 640 | 8.66154e+07 | 291297 | 0.479533 | 0.746426 | 3.27964 | 0.436428 | 0.00584581 | 0.0508055 | 0.00017885 | 2(Loss) | true |
