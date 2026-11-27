
----
### Canada Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1914.5 | 0.155325 | 9244.7ms | 5212421 | 40 | 6.50596e+08 | 2.59647e+06 | 0.207406 | 2.63794 | 12.0336 | 2.3013 | 0.00968926 | 0.0911344 | 0.000691195 | 1(Win) | true |
| simdjson (ondemand) | 1845.01 | 0.233995 | 9602.46ms | 5212421 | 40 | 1.58985e+09 | 2.69427e+06 | 0.867509 | 2.74986 | 12.6013 | 2.16734 | 0.00997452 | 0.110913 | 0.00078571 | 2(Loss) | true |
