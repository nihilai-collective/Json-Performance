
----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3930.01 | 0.0238425 | 4250.56ms | 124597 | 2560 | 133037 | 30235.3 | 0.0471836 | 1.29276 | 6.07112 | 1.01031 | 0.00261256 | 4.17283e-06 | 2.06917e-06 | 1(Win) | true |
| simdjson (ondemand) | 3045.59 | 0.0442815 | 5127.13ms | 124597 | 1280 | 382056 | 39015.4 | 0.0314037 | 1.67458 | 6.89678 | 1.09776 | 0.00499923 | 1.37945e-05 | 9.63105e-06 | 2(Loss) | true |
