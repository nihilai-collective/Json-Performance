
----
### Canada Test (Minified) Write (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2086.26 | 0.148767 | 6081ms | 2090326 | 30 | 6.06219e+07 | 955535 | 0.130465 | 2.444 | 7.7716 | 0.37332 | 0.000343567 | 0.0517533 | 4.47299e-05 | 1(Win) | true |
| simdjson (reflection) | 1616.94 | 0.0126699 | 7861.79ms | 2090326 | 80 | 1.95197e+06 | 1.23287e+06 | 0.175172 | 3.18224 | 10.1382 | 0.578319 | 0.00484789 | 0.0510773 | 7.34873e-05 | 2(Loss) | true |
| Glaze | 1547.61 | 0.0597809 | 8182.23ms | 2090234 | 160 | 9.48659e+07 | 1.28805e+06 | 0.131306 | 3.28216 | 9.5901 | 0.597292 | 0.0117445 | 0.0437892 | 6.50794e-05 | 3(Loss) | true |
