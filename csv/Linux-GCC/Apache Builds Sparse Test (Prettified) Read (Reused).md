
----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4119.29 | 0.0508354 | 4134.59ms | 124597 | 1280 | 275241 | 28846 | 0.0557284 | 1.24594 | 6.28651 | 0.987855 | 0.00233945 | 1.81209e-06 | 3.07241e-07 | 1(Win) | true |
| simdjson (ondemand) | 2975.27 | 0.0196656 | 5209.58ms | 124597 | 2560 | 157912 | 39937.5 | 0.0607812 | 1.72657 | 6.77893 | 1.13039 | 0.00474641 | 2.12874e-06 | 2.75889e-07 | 2(Loss) | true |
