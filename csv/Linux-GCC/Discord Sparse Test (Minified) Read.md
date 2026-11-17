
----
### Discord Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2493.82 | 0.0425622 | 2893.75ms | 56369 | 1280 | 107748 | 21556.4 | 0.0954252 | 2.06283 | 9.68004 | 1.70013 | 0.00374247 | 1.76987e-05 | 9.72942e-06 | 1(Win) | true |
| simdjson (ondemand) | 2162.82 | 0.0291812 | 3220.66ms | 56369 | 2560 | 134676 | 24855.4 | 0.0459244 | 2.37119 | 10.1759 | 1.70338 | 0.00462404 | 1.11154e-05 | 4.22024e-06 | 2(Loss) | true |
