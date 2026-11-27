
----
### Canada Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 11296.1 | 0.0556172 | 5724.61ms | 5212421 | 320 | 1.91687e+07 | 440060 | 0.0880505 | 0.44908 | 1.95452 | 0.198812 | 0.00212077 | 0.0393833 | 2.53541e-06 | 1(Win) | true |
| simdjson (ondemand) | 9577.12 | 0.0988729 | 6706.4ms | 5212421 | 160 | 4.2139e+07 | 519045 | 0.116294 | 0.52812 | 2.27763 | 0.20278 | 0.00214933 | 0.039457 | 5.50848e-06 | 2(Loss) | true |
