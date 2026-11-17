
----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11461.4 | 0.0385726 | 1188.43ms | 56369 | 2560 | 8379.2 | 4690.32 | 0.00792087 | 0.449612 | 2.3284 | 0.115845 | 3.68387e-05 | 3.02139e-06 | 9.771e-07 | 1(Win) | true |
| simdjson (stage-1) | 10405.1 | 0.0376288 | 1235.41ms | 56369 | 40 | 151.177 | 5166.45 | 0.00483915 | 0.498899 | 2.37178 | 0.103621 | 7.05175e-05 | 3.54805e-06 | 0 | 2(Loss) | true |
