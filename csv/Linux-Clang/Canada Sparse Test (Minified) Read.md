
----
### Canada Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 9155.33 | 0.0996179 | 5626.04ms | 2090234 | 320 | 1.50545e+07 | 217731 | 0.0913153 | 0.270382 | 1(Win) | true |
| simdjson (ondemand) | 7783.11 | 0.16303 | 6530.11ms | 2090234 | 1280 | 2.23166e+08 | 256119 | 0.0062966 | 0.318058 | 2(Loss) | true |
