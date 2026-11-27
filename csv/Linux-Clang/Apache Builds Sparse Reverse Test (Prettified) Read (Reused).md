
----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2809.91 | 0.0642061 | 5489.35ms | 124597 | 640 | 471806 | 42287.9 | 0.336178 | 1.8266 | 8.66387 | 1.60961 | 0.00461186 | 1.20639e-05 | 9.33008e-06 | 1(Win) | true |
| simdjson (ondemand) | 2455.78 | 0.051638 | 6041.12ms | 124597 | 1280 | 799067 | 48385.8 | 0.0148653 | 2.07645 | 8.91896 | 1.49972 | 0.00497624 | 1.14243e-05 | 8.37701e-06 | 2(Loss) | true |
