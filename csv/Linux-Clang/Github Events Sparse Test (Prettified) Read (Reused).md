
----
### Github Events Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9151.42 | 0.0557447 | 1423.98ms | 65103 | 640 | 9154.02 | 6784.42 | 0.139349 | 0.558317 | 2.55772 | 0.325315 | 0.000666396 | 2.18404e-06 | 3.84007e-07 | 1(Win) | true |
| simdjson (ondemand) | 8149.92 | 0.090859 | 1516.99ms | 65103 | 320 | 15331.4 | 7618.12 | 0.0285995 | 0.631689 | 2.85196 | 0.323011 | 0.000706189 | 2.01604e-06 | 9.60017e-08 | 2(Loss) | true |
