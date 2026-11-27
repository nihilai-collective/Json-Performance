
----
### Twitter Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8084.73 | 0.0651378 | 5012.14ms | 360584 | 1280 | 982557 | 42534.4 | 0.0121137 | 0.624369 | 2.94062 | 0.377158 | 0.00091721 | 3.42977e-06 | 1.87413e-06 | 1(Win) | true |
| simdjson (ondemand) | 7498.44 | 0.0458812 | 5353.38ms | 360584 | 640 | 283349 | 45860.1 | 0.0252743 | 0.677605 | 3.19559 | 0.335345 | 0.000734702 | 7.77385e-06 | 4.94424e-06 | 2(Loss) | true |
