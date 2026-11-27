
----
### Canada Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2316.84 | 0.057596 | 8042.08ms | 5373214 | 160 | 2.59645e+08 | 2.21176e+06 | 0.0952353 | 2.18289 | 11.7314 | 2.38101 | 0.00532936 | 0.0281163 | 0.000410512 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2208.83 | 0.0747567 | 8371.03ms | 5373214 | 160 | 4.81243e+08 | 2.31992e+06 | 0.0410544 | 2.29206 | 11.9583 | 2.22019 | 0.00672829 | 0.0523718 | 0.00012833 | 2(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 2205.12 | 0.216888 | 8340.36ms | 5373214 | 30 | 7.62075e+08 | 2.32382e+06 | 0.0997456 | 2.29707 | 10.8976 | 1.78195 | 0.00405931 | 0.0500181 | 0.000869287 | 2(Tie) | true |
| simdjson (ondemand) | 2012.57 | 0.0479993 | 9101.68ms | 5373214 | 160 | 2.38978e+08 | 2.54615e+06 | 0.251875 | 2.50799 | 11.5823 | 2.00522 | 0.00492352 | 0.0508827 | 0.00027584 | 4(Loss) | true |
| Glaze | 1828.29 | 0.150664 | 9849.89ms | 5373214 | 160 | 2.85311e+09 | 2.80278e+06 | 0.0429736 | 2.77062 | 13.8601 | 2.43497 | 0.00444959 | 0.0302188 | 0.000114148 | 5(Loss) | true |
