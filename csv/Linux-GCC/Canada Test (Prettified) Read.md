
----
### Canada Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 18122.6 | 0.118152 | 7667.2ms | 5373214 | 30 | 3.34835e+06 | 282758 | 0.922641 | 0.28435 | 1.36205 | 0.0692391 | 0.00102486 | 0.0195829 | 3.41199e-06 | 1(Win) | true |
| simdjson (stage-1) | 15789.8 | 0.138297 | 8535.07ms | 5373214 | 160 | 3.22298e+07 | 324532 | 0.250184 | 0.321243 | 1.59979 | 0.0578118 | 0.000932248 | 0.0195738 | 2.73928e-06 | 2(Loss) | true |
