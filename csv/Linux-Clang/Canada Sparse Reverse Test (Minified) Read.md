
----
### Canada Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5457.28 | 0.0751531 | 9530.62ms | 2090234 | 1280 | 9.64588e+07 | 365274 | 0.207511 | 0.936624 | 5.09756 | 0.738337 | 0.0026526 | 0.0744309 | 9.99985e-05 | 1(Win) | true |
| Jsonifier (generic) | 5379.41 | 0.137747 | 9699.93ms | 2090234 | 320 | 8.33751e+07 | 370562 | 0.0333921 | 0.953844 | 4.7195 | 0.756396 | 0.00580681 | 0.0757562 | 0.000109138 | 2(Loss) | true |
