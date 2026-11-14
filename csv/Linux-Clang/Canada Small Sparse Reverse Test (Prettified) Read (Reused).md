
----
### Canada Small Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10486.4 | 0.0544292 | 817.795ms | 11579 | 4890 | 1606.43 | 1053.04 | 0.0633396 | 0.510157 | 2.69661 | 0.342171 | 0.00025962 | 1.35815e-05 | 2.43724e-06 | 1(Win) | true |
| simdjson (ondemand) | 9272.66 | 0.0819859 | 831.966ms | 11579 | 640 | 610.086 | 1190.88 | 0.0749747 | 0.574312 | 2.94611 | 0.358667 | 0.000259899 | 2.96874e-06 | 0 | 2(Loss) | true |
