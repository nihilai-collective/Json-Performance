
----
### Twitter Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8830.95 | 0.0297992 | 4711ms | 360584 | 4890 | 658439 | 38940.3 | 0.0533898 | 0.571891 | 2.90947 | 0.343618 | 0.000828082 | 3.70281e-06 | 2.51183e-06 | 1(Win) | true |
| simdjson (ondemand) | 7622.43 | 0.0407069 | 5305.69ms | 360584 | 1280 | 431690 | 45114.2 | 0.0983751 | 0.662334 | 3.24057 | 0.322404 | 0.000918982 | 1.13076e-05 | 7.98184e-06 | 2(Loss) | true |
